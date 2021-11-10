#ifndef ROCKET_RENDER_H
#define ROCKET_RENDER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <RmlUi/Core.h>
#include <RmlUi/Core/RenderInterface.h>

class RocketRenderDirectX : public Rml::RenderInterface
{
private:
	LPDIRECT3D9 g_pD3D;
	LPDIRECT3DDEVICE9 g_pD3DDevice;
	void* m_context;

public:
	static RocketRenderDirectX m_Instance;
	RocketRenderDirectX();

	virtual void RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f& translation);

	virtual Rml::CompiledGeometryHandle CompileGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture);

	virtual void RenderCompiledGeometry(Rml::CompiledGeometryHandle geometry, const Rml::Vector2f& translation);
	virtual void ReleaseCompiledGeometry(Rml::CompiledGeometryHandle geometry);

	virtual void EnableScissorRegion(bool enable);
	virtual void SetScissorRegion(int x, int y, int width, int height);

	virtual bool LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source);
	virtual bool GenerateTexture(Rml::TextureHandle& texture_handle, const byte* source, const Rml::Vector2i& source_dimensions);
	virtual void ReleaseTexture(Rml::TextureHandle texture_handle);

	float GetHorizontalTexelOffset();
	float GetVerticalTexelOffset();

	inline void SetViewport(int width, int height)
	{
		if (g_pD3DDevice != NULL)
		{
			D3DXMATRIX projection;
			D3DXMatrixOrthoOffCenterLH(&projection, 0, (float)width, (float)height, 0, -1, 1);
			g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &projection);
		}

		if (m_context != NULL)
		{
			((Rml::Context*)m_context)->SetDimensions(Rml::Vector2i(width, height));
		}
	}

	inline bool AttachToNative(void* window)
	{
		RECT clientRect;
		if (!GetClientRect((HWND)window, &clientRect))
		{
			// if we can't lookup the client rect, abort, something is seriously wrong
			return false;
		}

		g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (g_pD3D == NULL)
			return false;

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		g_pD3DDevice = NULL;

		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			(HWND)window,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{

			this->DetachFromNative();
			return false;
		}

		// Set up an orthographic projection.
		D3DXMATRIX projection;
		D3DXMatrixOrthoOffCenterLH(&projection, 0, (FLOAT)clientRect.right, (FLOAT)clientRect.bottom, 0, -1, 1);

		g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &projection);

		// Switch to clockwise culling instead of counter-clockwise culling; Rocket generates counter-clockwise geometry,
		// so you can either reverse the culling mode when Rocket is rendering, or reverse the indices in the render
		// interface.
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		// Enable alpha-blending for Rocket.
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// Set up the texture stage states for the diffuse texture.
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

		// Disable lighting for Rocket.
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		return true;
	}

	inline void DetachFromNative()
	{
		if (g_pD3DDevice != NULL)
		{
			// Release the last resources we bound to the device.
			g_pD3DDevice->SetTexture(0, NULL);
			g_pD3DDevice->SetStreamSource(0, NULL, 0, 0);
			g_pD3DDevice->SetIndices(NULL);

			g_pD3DDevice->Release();
			g_pD3DDevice = NULL;
		}

		if (g_pD3D != NULL)
		{
			g_pD3D->Release();
			g_pD3D = NULL;
		}
	}

	inline void SetContext(void* context) { m_context = context; }
};

#endif