#include "RocketUIImpl.h"

#include "RocketSystem.h"
#include "RocketRenderDirectX.h"
#include "RocketFilesystem.h"
#include "RocketKeys.h"

#include "filesystem.h"
#include "inputsystem/AnalogCode.h"

#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>

RocketUIImpl RocketUIImpl::m_Instance;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR( RocketUIImpl, IRocketUI, ROCKETUI_INTERFACE_VERSION, RocketUIImpl::m_Instance )

ConVar rocket_enable("rocket_enable", "1", 0, "Enables RocketUI");
ConVar rocket_verbose("rocket_verbose", "0", 0, "Enables more logging");

CON_COMMAND_F(rocket_reload, "Reloads all RocketUI Documents", FCVAR_NONE)
{
	if (RocketUIImpl::m_Instance.ReloadDocuments())
	{
		ConMsg("[RocketUI] Documents Reloaded.\n");
	}
	else
	{
		ConMsg("[RocketUI] Error reloading Documents!\n");
	}
}

CON_COMMAND_F(rocket_debug, "Open/Close the RocketUI Debugger", FCVAR_NONE)
{
	RocketUIImpl::m_Instance.ToggleDebugger();
}

bool RocketUIImpl::Connect(CreateInterfaceFn factory)
{
	if (!factory)
	{
		return false;
	}

	if (!BaseClass::Connect(factory))
	{
		return false;
	}

	m_pShaderDeviceMgr = (IShaderDeviceMgr*)factory(SHADER_DEVICE_MGR_INTERFACE_VERSION, NULL);
	m_pGameUIFuncs = (IGameUIFuncs*)factory(VENGINE_GAMEUIFUNCS_VERSION, NULL);
	m_pEngine = (IVEngineClient*)factory(VENGINE_CLIENT_INTERFACE_VERSION, NULL);
	m_pGameEventManager = (IGameEventManager2*)factory(INTERFACEVERSION_GAMEEVENTSMANAGER2, NULL);
	m_pShaderAPI = (IShaderAPI *)factory(SHADERAPI_INTERFACE_VERSION, NULL);

	if (!m_pShaderDeviceMgr || !m_pGameUIFuncs || !m_pEngine || !m_pGameEventManager || !m_pShaderAPI)
	{
		Warning("RocketUI: missing expected interface\n");
		return false;
	}

	return true;
}

void RocketUIImpl::Disconnect()
{
	m_pShaderDeviceMgr = NULL;
	m_pGameUIFuncs = NULL;
	m_pEngine = NULL;
	m_pGameEventManager = NULL;
	m_pShaderAPI = NULL;

	BaseClass::Disconnect();
}

void* RocketUIImpl::QueryInterface(const char *pInterfaceName)
{
	if (!Q_strncmp(pInterfaceName, ROCKETUI_INTERFACE_VERSION, Q_strlen(ROCKETUI_INTERFACE_VERSION) + 1))
	{
		return (IRocketUI*)&RocketUIImpl::m_Instance;
	}

	return BaseClass::QueryInterface(pInterfaceName);
}

Rml::Context* RocketUIImpl::AccessHudContext()
{
	return m_ctxHud;
}

Rml::Context* RocketUIImpl::AccessMenuContext()
{
	return m_ctxMenu;
}

bool RocketUIImpl::LoadFont(const char *filepath, const char *path)
{
	unsigned char *fontBuffer = NULL;
	CUtlBuffer font;
	unsigned int fontLen;

	if (!g_pFullFileSystem->ReadFile(filepath, path, font))
	{
		fprintf(stderr, "[RocketUI] Failed to read %s font.", filepath);
		return false;
	}

	fontLen = font.Size() - 1;

	if (fontLen >= (8 * 1024 * 1024))
	{
		fprintf(stderr, "[RocketUI] Font (%s) is over 8MB!(%d). Not Loading.\n", filepath, fontLen);
		return false;
	}

	fprintf(stderr, "[RocketUI] Font size (%d)\n", fontLen);

	fontBuffer = new unsigned char[fontLen + 1];
	// Add to list of alloc'd fonts. Freetype will use this memory until we Shutdown.
	m_fontAllocs.AddToTail(fontBuffer);

	font.Get(fontBuffer, fontLen);

	if (!Rml::LoadFontFace(fontBuffer, fontLen, "Lato", Rml::Style::FontStyle::Normal, Rml::Style::FontWeight::Normal, false))
	{
		fprintf(stderr, "[RocketUI] Failed to Initialize Lato font\n");
		return false;
	}

	return true;
}

bool RocketUIImpl::LoadFonts()
{
	bool fontsOK = true;
	fontsOK &= LoadFont("rocketui/fonts/Lato-Black.ttf", "GAME");

	return fontsOK;
}

Rml::ElementDocument *RocketUIImpl::LoadDocumentFile(RocketDesinationContext_t ctx, const char *filepath, LoadDocumentFn loadDocumentFunc, UnloadDocumentFn unloadDocumentFunc)
{
	Rml::ElementDocument *document;
	Rml::Context *destinationCtx;

	switch (ctx)
	{
	case ROCKET_CONTEXT_MENU:
		destinationCtx = m_ctxMenu;
		break;
	case ROCKET_CONTEXT_HUD:
		destinationCtx = m_ctxHud;
		break;
	case ROCKET_CONTEXT_CURRENT:
		if (!m_ctxCurrent)
		{
			Error("Couldn't load document: %s - loaded before 1st frame.\n", filepath);
			return nullptr;
		}
		destinationCtx = m_ctxCurrent;
		break;
	default:
		return nullptr;
	}

	document = destinationCtx->LoadDocument(filepath);

	// Need both
	if (loadDocumentFunc && unloadDocumentFunc)
	{
		CUtlPair<LoadDocumentFn, UnloadDocumentFn> documentFuncPair(loadDocumentFunc, unloadDocumentFunc);
		CUtlPair<RocketDesinationContext_t, CUtlPair<LoadDocumentFn, UnloadDocumentFn>> reloadFunctionEntry(ctx, documentFuncPair);
		m_documentReloadFuncs.AddToTail(reloadFunctionEntry);
	}

	return document;
}

InitReturnVal_t RocketUIImpl::Init(void)
{
	InitReturnVal_t nRetVal = BaseClass::Init();
	if (nRetVal != INIT_OK)
	{
		return nRetVal;
	}

	// Create/Init the RmlUi
	RocketRenderDirectX::m_Instance.SetViewport(1024, 768);

	Rml::SetFileInterface(&RocketFilesystem::m_Instance);
	Rml::SetRenderInterface(&RocketRenderDirectX::m_Instance);
	Rml::SetSystemInterface(&RocketSystem::m_Instance);

	if (!Rml::Initialise())
	{
		Warning("RocketUI: Initialise() failed!\n");
		return INIT_FAILED;
	}

	if (!LoadFonts())
	{
		Warning("RocketUI: Failed to load fonts.\n");
		return INIT_FAILED;
	}

	m_ctxMenu = Rml::CreateContext("menu", Rml::Vector2i(1024, 768));
	m_ctxHud = Rml::CreateContext("hud", Rml::Vector2i(1024, 768));

	if (!m_ctxMenu || !m_ctxHud)
	{
		Warning("RocketUI: Failed to create Hud/Menu context\n");
		Rml::Shutdown();
		return INIT_FAILED;
	}

	m_ctxMenu->SetDensityIndependentPixelRatio(1.0f);
	m_ctxHud->SetDensityIndependentPixelRatio(1.0f);

	return INIT_OK;
}

void RocketUIImpl::Shutdown()
{
	// Shutdown RocketUI. All contexts are destroyed on shutdown.
	Rml::Shutdown();

	// freetype FT_Done_Face has been called. Time to free fonts.
	for (int i = 0; i < m_fontAllocs.Count(); i++)
	{
		unsigned char *fontAlloc = m_fontAllocs[i];
		delete[] fontAlloc;
	}

	m_ctxCurrent = NULL;

	BaseClass::Shutdown();
}

void RocketUIImpl::RunFrame(float time)
{
	// We dont have the device yet..
	if (!m_pDevice)
		return;

	m_fTime = time;

	// This is important. Update the current context 1x per frame.
	// This basically needs to be called whenever elements are added/changed/removed
	// I am calling it 1x per frame here instead of all over the place for simplicity and no overlap.
	if (m_ctxCurrent)
		m_ctxCurrent->Update();
}

void RocketUIImpl::DenyInputToGame(bool value, const char *why)
{
	if (value)
	{
		m_numInputConsumers++;
		m_inputConsumers.AddToTail(CUtlString(why));
	}
	else
	{
		m_numInputConsumers--;
		m_inputConsumers.FindAndRemove(CUtlString(why));
	}

	EnableCursor((m_numInputConsumers > 0));

	if (rocket_verbose.GetBool())
	{
		ConMsg("input Consumers[%d]: ", m_numInputConsumers);
		for (int i = 0; i < m_inputConsumers.Count(); i++)
		{
			ConMsg("(%s) ", m_inputConsumers[i].Get());
		}
		ConMsg("\n");
	}
}

bool RocketUIImpl::IsConsumingInput()
{
	return (m_numInputConsumers > 0);
}

void RocketUIImpl::EnableCursor(bool state)
{
	ConVarRef cl_mouseenable("cl_mouseenable");

	cl_mouseenable.SetValue(!state);

	m_bCursorVisible = state;
}

// This function is an input hook.
// return true if we want to deny the game the input.
bool RocketUIImpl::HandleInputEvent(const InputEvent_t &event)
{
	// Haven't rendered our very first frame ever yet.
	if (!m_ctxCurrent)
		return false;

	if (!rocket_enable.GetBool())
		return false;

	// Always get the mouse location.
	if (event.m_nType == IE_AnalogValueChanged && event.m_nData == MOUSE_XY)
	{
		// TODO update this with keymodifiers
		m_ctxCurrent->ProcessMouseMove(event.m_nData2, event.m_nData3, 0);
	}

	// Some edge cases
	if (event.m_nType == IE_ButtonPressed)
	{
		if (event.m_nData == KEY_BACKQUOTE)
		{
			m_pEngine->ClientCmd_Unrestricted("toggleconsole");
		}

		// Check for debugger. Toggle on F8.
		if (event.m_nData == KEY_F8)
		{
			ToggleDebugger();
			return true;
		}
		// The magical ESC key for the pause menu. The game handles this in an awful way
		// CSGO will open the pause menu for us the 1st time, but after that it fubars
		// In order to minimize this component from reaching into the gamecode,
		// The pause menu will register itself via RegisterPauseMenu while loading.
		// Kinda Hacky, but it is direct from keys.cpp and prevents the VGUI code from messing with it too much.
		if (event.m_nData == KEY_ESCAPE)
		{
			if (m_togglePauseMenuFunc && m_pEngine->IsInGame())
			{
				m_togglePauseMenuFunc();
			}
		}
	}

	// Nothing wants input, skip.
	if (!IsConsumingInput())
		return false;

	// The console is open, skip
	if (m_pEngine->Con_IsVisible())
		return false;

	Rml::Input::KeyIdentifier key;
	char ascii;

	switch (event.m_nType)
	{
	case IE_ButtonDoubleClicked:
	case IE_ButtonPressed:
		//TODO add key modifiers
		if (IsMouseCode((ButtonCode_t)event.m_nData))
		{
			switch ((ButtonCode_t)event.m_nData)
			{
			case MOUSE_LEFT:
				m_ctxCurrent->ProcessMouseButtonDown(0, 0);
				break;
			case MOUSE_RIGHT:
				m_ctxCurrent->ProcessMouseButtonDown(1, 0);
				break;
			case MOUSE_MIDDLE:
				m_ctxCurrent->ProcessMouseButtonDown(2, 0);
				break;
			case MOUSE_4:
				m_ctxCurrent->ProcessMouseButtonDown(3, 0);
				break;
			case MOUSE_5:
				m_ctxCurrent->ProcessMouseButtonDown(4, 0);
				break;
			case MOUSE_WHEEL_UP:
				m_ctxCurrent->ProcessMouseWheel(-1, 0);
				break;
			case MOUSE_WHEEL_DOWN:
				m_ctxCurrent->ProcessMouseWheel(1, 0);
				break;
			}
		}
		else
		{
			m_ctxCurrent->ProcessKeyDown(ButtonToRocketKey((ButtonCode_t)event.m_nData), 0);
		}
		break;
	case IE_ButtonReleased:
		//TODO add key modifiers
		if (IsMouseCode((ButtonCode_t)event.m_nData))
		{
			switch ((ButtonCode_t)event.m_nData)
			{
			case MOUSE_LEFT:
				m_ctxCurrent->ProcessMouseButtonUp(0, 0);
				break;
			case MOUSE_RIGHT:
				m_ctxCurrent->ProcessMouseButtonUp(1, 0);
				break;
			case MOUSE_MIDDLE:
				m_ctxCurrent->ProcessMouseButtonUp(2, 0);
				break;
			case MOUSE_4:
				m_ctxCurrent->ProcessMouseButtonUp(3, 0);
				break;
			case MOUSE_5:
				m_ctxCurrent->ProcessMouseButtonUp(4, 0);
				break;
			}
		}
		else
		{
			m_ctxCurrent->ProcessKeyUp(ButtonToRocketKey((ButtonCode_t)event.m_nData), 0);
		}
		break;
	case IE_KeyTyped:
		ascii = (char)((wchar_t)event.m_nData);
		if (ascii != 8) { // Rocketui doesn't like the backspace for some reason.
			m_ctxCurrent->ProcessTextInput(ascii);
		}
		break;
	case IE_AnalogValueChanged:
		// Mouse/Joystick changes. Mouse changes are recorded above
		break;

	default:
		return false;
	}

	return IsConsumingInput();
}

void RocketUIImpl::RenderHUDFrame()
{
	if (!rocket_enable.GetBool())
		return;

	m_ctxCurrent = m_ctxHud;

	m_ctxHud->Render();
}

void RocketUIImpl::RenderMenuFrame()
{
	if (!rocket_enable.GetBool())
		return;

	m_ctxCurrent = m_ctxMenu;

	//TODO: don't update here. update only after input or new elements
	//m_ctxMenu->Update();

	RocketRenderDirectX::m_Instance.PrepareRenderBuffer();
	m_ctxMenu->Render();
	RocketRenderDirectX::m_Instance.PresentRenderBuffer();
}

bool RocketUIImpl::ReloadDocuments()
{
	rocket_enable.SetValue(false);
	// Hacky, sleep for 100ms after disabling UI.
	// I dont feel like adding a mutex check every frame for something rarely used by devs
	// TODO: mutex
	ThreadSleep(100);

	CUtlVector< CUtlPair< RocketDesinationContext_t, CUtlPair<LoadDocumentFn, UnloadDocumentFn> > > copyOfPairs;

	// Copy the pairs into a local Vector( grug, copy constructor no work )
	// We want a copy because the loading functions will mess with our Vector when we call them.
	for (int i = 0; i < m_documentReloadFuncs.Count(); i++)
	{
		copyOfPairs.AddToTail(m_documentReloadFuncs[i]);
	}

	// We can now empty the Main Vector since we are about to reload.
	m_documentReloadFuncs.Purge();

	// Go through the copy and reload
	for (int i = 0; i < copyOfPairs.Count(); i++)
	{
		// Only reload the ones for the current context!
		if (copyOfPairs[i].first == ROCKET_CONTEXT_HUD && m_ctxCurrent != m_ctxHud)
			continue;
		if (copyOfPairs[i].first == ROCKET_CONTEXT_MENU && m_ctxCurrent != m_ctxMenu)
			continue;
		if (copyOfPairs[i].first == ROCKET_CONTEXT_CURRENT)
		{
			// Unload only, these should only be used for popups/etc
			copyOfPairs[i].second.second();
			continue;
		}

		// Unload...
		copyOfPairs[i].second.second();
		// Load...
		copyOfPairs[i].second.first();
	}

	rocket_enable.SetValue(true);
	return true;
}

void RocketUIImpl::AddDeviceDependentObject( IShaderDeviceDependentObject *pObject )
{
	if ( m_pShaderDeviceMgr ) 
		m_pShaderDeviceMgr->AddDeviceDependentObject( pObject );
}

void RocketUIImpl::RemoveDeviceDependentObject( IShaderDeviceDependentObject *pObject )
{
	if ( m_pShaderDeviceMgr )
		m_pShaderDeviceMgr->RemoveDeviceDependentObject( pObject );
}

void RocketUIImpl::SetRenderingDevice(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPresentParameters, HWND hWnd)
{
	if ( !pDevice || m_pDevice != pDevice )
		m_pDevice = pDevice;

	D3DVIEWPORT9 viewport;
	pDevice->GetViewport( &viewport );
	SetViewport( viewport.Width, viewport.Height );
	RocketRenderDirectX::m_Instance.SetRenderingDevice( pDevice );
}

void RocketUIImpl::NotifyRenderingDeviceLost()
{
	if ( m_pDevice == NULL ) return;

	m_pDevice->Release();
	m_pDevice = NULL;
}

void RocketUIImpl::SetViewport(int width, int height)
{
	m_ctxCurrent = nullptr;

	m_ctxHud->SetDimensions(Rml::Vector2i(width, height));
	m_ctxMenu->SetDimensions(Rml::Vector2i(width, height));

	RocketRenderDirectX::m_Instance.SetViewport(width, height);
}

void RocketUIImpl::ToggleDebugger()
{
	static bool open = false;
	static bool firstTime = true;

	open = !open;

	if (!m_ctxCurrent)
		return;

	if (open)
	{
		if (firstTime)
		{
			if (Rml::Debugger::Initialise(m_ctxCurrent))
			{
				firstTime = false;
			}
			else
			{
				ConMsg("[RocketUI] Error Initializing Debugger\n");
				return;
			}
		}
		ConMsg("[RocketUI] Opening Debugger\n");
		if (!Rml::Debugger::SetContext(m_ctxCurrent))
		{
			ConMsg("[RocketUI] Error setting context!\n");
			return;
		}
	 	m_debuggerToggle = true;
		Rml::Debugger::SetVisible(true);
		DenyInputToGame(true, "RocketUI Debugger");
	}
	else
	{
		ConMsg("[RocketUI] Closing Debugger\n");
		Rml::Debugger::SetVisible(false);
		m_debuggerToggle = false;
		DenyInputToGame(false, "RocketUI Debugger");
	}
}