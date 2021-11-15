#ifndef ROCKETUI_IMPL_H
#define ROCKETUI_IMPL_H

#include "rocketui/rocketui.h"
#include "RocketRenderDirectX.h"

#include <appframework/IAppSystemGroup.h>
#include <tier1/utlpair.h>
#include <tier3/tier3.h>
#include <shaderapi/ishaderapi.h>
#include <shaderapi/IShaderDevice.h>
#include <igameevents.h>
#include <IGameUIFuncs.h>
#include <cdll_int.h>

#include <RmlUi/Core/ElementDocument.h>

class RocketUIImpl : public CTier3AppSystem<IRocketUI>
{
	typedef CTier3AppSystem<IRocketUI> BaseClass;

protected:
	IDirect3DDevice9    *m_pDevice;

	IShaderDeviceMgr    *m_pShaderDeviceMgr;
	IShaderAPI		    *m_pShaderAPI;
	IGameUIFuncs        *m_pGameUIFuncs;
	IVEngineClient      *m_pEngine;
	IGameEventManager2  *m_pGameEventManager;

	// Fonts need to stay for the lifetime of the program. Used directly by freetype. Freed on shutdown.
	CUtlVector<unsigned char*>   m_fontAllocs;
	CUtlVector<CUtlString>       m_inputConsumers;
	float               m_fTime;
	bool                m_bCursorVisible;

	// Contexts
	Rml::Context* m_ctxMenu;
	Rml::Context *m_ctxHud;
	Rml::Context *m_ctxCurrent; //Pointer to Hud or Menu

	bool m_debuggerToggle;

	TogglePauseMenuFn m_togglePauseMenuFunc;

	// List of Document Reload functions for hot-reloading.
	// Has a DestinationContext, and then an Load/Unload function ptr for each entry.
	CUtlVector<
		CUtlPair<RocketDesinationContext_t, CUtlPair<LoadDocumentFn, UnloadDocumentFn>>
	> m_documentReloadFuncs;

	// if > 0, we are stealing input from the game.
	int m_numInputConsumers;
	// IAppSystem
public:
	virtual bool Connect(CreateInterfaceFn factory);
	virtual void Disconnect(void);

	virtual void *QueryInterface(const char *pInterfaceName);

	virtual InitReturnVal_t Init(void);
	virtual void Shutdown(void);

	// IRocketUI
public:
	// Updates time mostly
	virtual void RunFrame(float time);

	// Reload from Disk
	virtual bool ReloadDocuments();

	// Feed input into UI
	virtual bool HandleInputEvent(const InputEvent_t &event);
	// Start consuming inputs
	virtual void DenyInputToGame(bool value, const char *why);
	virtual bool IsConsumingInput(void);

	virtual void EnableCursor(bool state);

	// Document manipulation.
	virtual Rml::ElementDocument *LoadDocumentFile(RocketDesinationContext_t ctx, const char *filepath,
		LoadDocumentFn loadDocumentFunc = nullptr, UnloadDocumentFn unloadDocumentFunc = nullptr);

	// Rendering
	virtual void RenderHUDFrame();
	virtual void RenderMenuFrame();

	// Access to the actual contexts.
	virtual Rml::Context* AccessHudContext();
	virtual Rml::Context* AccessMenuContext();

	virtual void RegisterPauseMenu(TogglePauseMenuFn showPauseMenuFunc)
	{
		m_togglePauseMenuFunc = showPauseMenuFunc;
	}

	void AddDeviceDependentObject( IShaderDeviceDependentObject * pObject );
	void RemoveDeviceDependentObject( IShaderDeviceDependentObject * pObject );

	// Local Class Methods
	void SetRenderingDevice(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPresentParameters, HWND hWnd);

	void NotifyRenderingDeviceLost();

	void ToggleDebugger();

	Rml::Context *GetCurrentContext() { return m_ctxCurrent; }

	inline static RocketUIImpl* GetInstance() { return &m_Instance; }

private:
	bool LoadFont(const char *filepath, const char *path);
	bool LoadFonts();

public:
	static RocketUIImpl m_Instance;

	inline const float GetTime() { return m_fTime; }

	void SetViewport(int width, int height);
};

class DeviceCallbacks : public IShaderDeviceDependentObject
{
public:
	int m_iRefCount;
	RocketUIImpl* m_pRocketUI;

	DeviceCallbacks( void ) :
		m_iRefCount( 1 ), m_pRocketUI( NULL )
	{
	}

	virtual void DeviceLost( void )
	{
		m_pRocketUI->NotifyRenderingDeviceLost();
	}

	virtual void DeviceReset( void *pDevice, void *pPresentParameters, void *pHWnd )
	{
		m_pRocketUI->SetRenderingDevice( (IDirect3DDevice9*)pDevice, (D3DPRESENT_PARAMETERS*)pPresentParameters, (HWND)pHWnd );
	}

	virtual void ScreenSizeChanged( int width, int height )
	{
		m_pRocketUI->SetViewport( width, height );
	}
};

#endif