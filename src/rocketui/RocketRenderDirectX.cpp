#include "RocketRenderDirectX.h"

#include <RmlUi/Core/FileInterface.h>

// Most code from https://github.com/libRocket/libRocket/blob/master/Samples/basic/directx/src/RenderInterfaceDirectX.cpp

RocketRenderDirectX RocketRenderDirectX::m_Instance;

struct D3D9CompiledGeometry
{
	LPDIRECT3DVERTEXBUFFER9 vertices;
	DWORD num_vertices;

	LPDIRECT3DINDEXBUFFER9 indices;
	DWORD num_primitives;

	LPDIRECT3DTEXTURE9 texture;
};

struct D3D9Vertex
{
	FLOAT x, y, z;
	DWORD colour;
	FLOAT u, v;
};

DWORD vertex_fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

RocketRenderDirectX::RocketRenderDirectX()
{
	g_pD3D = NULL;
	g_pD3DDevice = NULL;
	m_context = NULL;
}

// Called by Rocket when it wants to render geometry that it does not wish to optimise.
void RocketRenderDirectX::RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rml::TextureHandle texture, const Rml::Vector2f& translation)
{
	if (g_pD3DDevice == NULL)
	{
		return;
	}

	Rml::CompiledGeometryHandle geom = this->CompileGeometry(vertices, num_vertices, indices, num_indices, texture);
	this->RenderCompiledGeometry(geom, translation);
	this->ReleaseCompiledGeometry(geom);
}

// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
Rml::CompiledGeometryHandle RocketRenderDirectX::CompileGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture)
{
	if (g_pD3DDevice == NULL)
	{
		return false;
	}

	// Construct a new D3D9CompiledGeometry structure, which will be returned as the handle, and the buffers to
	// store the geometry.
	D3D9CompiledGeometry* geometry = new D3D9CompiledGeometry();
	g_pD3DDevice->CreateVertexBuffer(num_vertices * sizeof(D3D9Vertex), D3DUSAGE_WRITEONLY, vertex_fvf, D3DPOOL_DEFAULT, &geometry->vertices, NULL);
	g_pD3DDevice->CreateIndexBuffer(num_indices * sizeof(unsigned int), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &geometry->indices, NULL);

	// Fill the vertex buffer.
	D3D9Vertex* d3d9_vertices;
	geometry->vertices->Lock(0, 0, (void**)&d3d9_vertices, 0);
	for (int i = 0; i < num_vertices; ++i)
	{
		d3d9_vertices[i].x = vertices[i].position.x;
		d3d9_vertices[i].y = vertices[i].position.y;
		d3d9_vertices[i].z = 0;

		d3d9_vertices[i].colour = D3DCOLOR_RGBA(vertices[i].colour.red, vertices[i].colour.green, vertices[i].colour.blue, vertices[i].colour.alpha);

		d3d9_vertices[i].u = vertices[i].tex_coord[0];
		d3d9_vertices[i].v = vertices[i].tex_coord[1];
	}
	geometry->vertices->Unlock();

	// Fill the index buffer.
	unsigned int* d3d9_indices;
	geometry->indices->Lock(0, 0, (void**)&d3d9_indices, 0);
	memcpy(d3d9_indices, indices, sizeof(unsigned int) * num_indices);
	geometry->indices->Unlock();

	geometry->num_vertices = (DWORD)num_vertices;
	geometry->num_primitives = (DWORD)num_indices / 3;

	geometry->texture = texture == NULL ? NULL : (LPDIRECT3DTEXTURE9)texture;

	return (Rml::CompiledGeometryHandle)geometry;
}

// Called by Rocket when it wants to render application-compiled geometry.
void RocketRenderDirectX::RenderCompiledGeometry(Rml::CompiledGeometryHandle geometry, const Rml::Vector2f& translation)
{
	if (g_pD3DDevice == NULL)
	{
		return;
	}

	// Build and set the transform matrix.
	D3DXMATRIX world_transform;
	D3DXMatrixTranslation(&world_transform, translation.x, translation.y, 0);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world_transform);

	D3D9CompiledGeometry* d3d9_geometry = (D3D9CompiledGeometry*)geometry;

	// Set the vertex format for the Rocket vertices, and bind the vertex and index buffers.
	g_pD3DDevice->SetFVF(vertex_fvf);
	g_pD3DDevice->SetStreamSource(0, d3d9_geometry->vertices, 0, sizeof(D3D9Vertex));
	g_pD3DDevice->SetIndices(d3d9_geometry->indices);

	// Set the texture, if this geometry has one.
	if (d3d9_geometry->texture != NULL)
		g_pD3DDevice->SetTexture(0, d3d9_geometry->texture);
	else
		g_pD3DDevice->SetTexture(0, NULL);

	// Draw the primitives.
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, d3d9_geometry->num_vertices, 0, d3d9_geometry->num_primitives);
}

// Called by Rocket when it wants to release application-compiled geometry.
void RocketRenderDirectX::ReleaseCompiledGeometry(Rml::CompiledGeometryHandle geometry)
{
	D3D9CompiledGeometry* d3d9_geometry = (D3D9CompiledGeometry*)geometry;

	d3d9_geometry->vertices->Release();
	d3d9_geometry->indices->Release();

	delete d3d9_geometry;
}

// Called by Rocket when it wants to enable or disable scissoring to clip content.
void RocketRenderDirectX::EnableScissorRegion(bool enable)
{
	if (g_pD3DDevice == NULL)
	{
		return;
	}

	g_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, enable);
}

// Called by Rocket when it wants to change the scissor region.
void RocketRenderDirectX::SetScissorRegion(int x, int y, int width, int height)
{
	if (g_pD3DDevice == NULL)
	{
		return;
	}

	RECT scissor_rect;
	scissor_rect.left = x;
	scissor_rect.right = x + width;
	scissor_rect.top = y;
	scissor_rect.bottom = y + height;

	g_pD3DDevice->SetScissorRect(&scissor_rect);
}

// Set to byte packing, or the compiler will expand our struct, which means it won't read correctly from file
#pragma pack(1) 
struct TGAHeader
{
	char  idLength;
	char  colourMapType;
	char  dataType;
	short int colourMapOrigin;
	short int colourMapLength;
	char  colourMapDepth;
	short int xOrigin;
	short int yOrigin;
	short int width;
	short int height;
	char  bitsPerPixel;
	char  imageDescriptor;
};
// Restore packing
#pragma pack()

// Called by Rocket when a texture is required by the library.
bool RocketRenderDirectX::LoadTexture(Rml::TextureHandle& texture_handle, Rml::Vector2i& texture_dimensions, const Rml::String& source)
{
	if (g_pD3DDevice == NULL)
	{
		return false;
	}

	Rml::FileInterface* file_interface = Rml::GetFileInterface();
	Rml::FileHandle file_handle = file_interface->Open(source);
	if (file_handle == NULL)
		return false;

	file_interface->Seek(file_handle, 0, SEEK_END);
	size_t buffer_size = file_interface->Tell(file_handle);
	file_interface->Seek(file_handle, 0, SEEK_SET);

	char* buffer = new char[buffer_size];
	file_interface->Read(buffer, buffer_size, file_handle);
	file_interface->Close(file_handle);

	TGAHeader header;
	memcpy(&header, buffer, sizeof(TGAHeader));

	int color_mode = header.bitsPerPixel / 8;
	int image_size = header.width * header.height * 4; // We always make 32bit textures 

	if (header.dataType != 2)
	{
		Rml::Log::Message(Rml::Log::LT_ERROR, "Only 24/32bit uncompressed TGAs are supported.");
		return false;
	}

	// Ensure we have at least 3 colors
	if (color_mode < 3)
	{
		Rml::Log::Message(Rml::Log::LT_ERROR, "Only 24 and 32bit textures are supported");
		return false;
	}

	const char* image_src = buffer + sizeof(TGAHeader);
	unsigned char* image_dest = new unsigned char[image_size];

	// Targa is BGR, swap to RGB and flip Y axis
	for (long y = 0; y < header.height; y++)
	{
		long read_index = y * header.width * color_mode;
		long write_index = ((header.imageDescriptor & 32) != 0) ? read_index : (header.height - y - 1) * header.width * color_mode;
		for (long x = 0; x < header.width; x++)
		{
			image_dest[write_index] = image_src[read_index + 2];
			image_dest[write_index + 1] = image_src[read_index + 1];
			image_dest[write_index + 2] = image_src[read_index];
			if (color_mode == 4)
				image_dest[write_index + 3] = image_src[read_index + 3];
			else
				image_dest[write_index + 3] = 255;

			write_index += 4;
			read_index += color_mode;
		}
	}

	texture_dimensions.x = header.width;
	texture_dimensions.y = header.height;

	bool success = GenerateTexture(texture_handle, image_dest, texture_dimensions);

	delete[] image_dest;
	delete[] buffer;

	return success;
}

// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
bool RocketRenderDirectX::GenerateTexture(Rml::TextureHandle& texture_handle, const byte* source, const Rml::Vector2i& source_dimensions)
{
	if (g_pD3DDevice == NULL)
	{
		return false;
	}

	// Create a Direct3DTexture9, which will be set as the texture handle. Note that we only create one surface for
	// this texture; because we're rendering in a 2D context, mip-maps are not required.
	LPDIRECT3DTEXTURE9 d3d9_texture;
	if (g_pD3DDevice->CreateTexture(source_dimensions.x, source_dimensions.y, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &d3d9_texture, NULL) != D3D_OK)
		return false;

	// Lock the top surface and write the pixel data onto it.
	D3DLOCKED_RECT locked_rect;
	d3d9_texture->LockRect(0, &locked_rect, NULL, 0);
	for (int y = 0; y < source_dimensions.y; ++y)
	{
		for (int x = 0; x < source_dimensions.x; ++x)
		{
			const byte* source_pixel = source + (source_dimensions.x * 4 * y) + (x * 4);
			byte* destination_pixel = ((byte*)locked_rect.pBits) + locked_rect.Pitch * y + x * 4;

			destination_pixel[0] = source_pixel[2];
			destination_pixel[1] = source_pixel[1];
			destination_pixel[2] = source_pixel[0];
			destination_pixel[3] = source_pixel[3];
		}
	}
	d3d9_texture->UnlockRect(0);

	// Set the handle on the Rocket texture structure.
	texture_handle = (Rml::TextureHandle)d3d9_texture;
	return true;
}

// Called by Rocket when a loaded texture is no longer required.
void RocketRenderDirectX::ReleaseTexture(Rml::TextureHandle texture_handle)
{
	((LPDIRECT3DTEXTURE9)texture_handle)->Release();
}

// Returns the native horizontal texel offset for the renderer.
float RocketRenderDirectX::GetHorizontalTexelOffset()
{
	return -0.5f;
}

// Returns the native vertical texel offset for the renderer.
float RocketRenderDirectX::GetVerticalTexelOffset()
{
	return -0.5f;
}