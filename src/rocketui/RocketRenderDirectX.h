#ifndef ROCKET_RENDER_H
#define ROCKET_RENDER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <RmlUi/Core.h>
#include <RmlUi/Core/RenderInterface.h>

class RocketRenderDirectX : public Rml::RenderInterface
{
private:
	int m_Width;
	int m_Height;
	Rml::Context* m_pRocketContext;
	IDirect3DDevice9* m_pRenderDevice;

public:
	static RocketRenderDirectX m_Instance;

	// Called by RmlUi when it wants to render geometry that the application does not wish to optimise.
	virtual void RenderGeometry(Rml::Vertex* vertices, int num_vertices,
		int* indices, int num_indices,
		Rml::TextureHandle texture, const Rml::Vector2f& translation) override;

	// Called by RmlUi when it wants to compile geometry it believes will be static for the forseeable future.
	virtual Rml::CompiledGeometryHandle CompileGeometry(Rml::Vertex* vertices, int num_vertices,
		int* indices, int num_indices, Rml::TextureHandle texture) override;

	// Called by RmlUi when it wants to render application-compiled geometry.
	virtual void RenderCompiledGeometry(Rml::CompiledGeometryHandle geometry, const Rml::Vector2f& translation);

	// Called by RmlUi when it wants to release application-compiled geometry.
	virtual void ReleaseCompiledGeometry(Rml::CompiledGeometryHandle geometry) override;

	// Called by RmlUi when it wants to enable or disable scissoring to clip content.
	virtual void EnableScissorRegion(bool enable) override;

	// Called by RmlUi when it wants to change the scissor region.
	virtual void SetScissorRegion(int x, int y, int width, int height) override;

	// Called by RmlUi when a texture is required by the library.
	virtual bool LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions,
		const Rml::String& source) override;

	// Called by RmlUi when a texture is required to be built from an internally-generated sequence of pixels.
	virtual bool GenerateTexture(Rml::TextureHandle& texture_handle,
		const Rml::byte* source, const Rml::Vector2i& source_dimensions) override;
	
	// Called by RmlUi when a loaded texture is no longer required.
	virtual void ReleaseTexture(Rml::TextureHandle texture) override;

	// RenderInterface Extensions
	inline void SetRenderingDevice(IDirect3DDevice9* device) { m_pRenderDevice = device; }

	inline void PrepareRenderBuffer()
	{
		m_pRenderDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		m_pRenderDevice->BeginScene();
	}

	inline void PresentRenderBuffer()
	{
		m_pRenderDevice->EndScene();
		m_pRenderDevice->Present(NULL, NULL, NULL, NULL);
	}

	// TODO: use in code
	inline void SetContext(Rml::Context* context)
	{
		m_pRocketContext = context;
	}

	inline void SetViewport(int width, int height)
	{
		m_Width = width;
		m_Height = height;
	}
};

#endif