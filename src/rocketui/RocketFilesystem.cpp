#include "RocketFilesystem.h"

#include "filesystem.h"

RocketFilesystem RocketFilesystem::m_Instance;

RocketFilesystem::RocketFilesystem() { }

Rml::FileHandle RocketFilesystem::Open(const Rml::String &path)
{
	return (Rml::FileHandle)g_pFullFileSystem->Open(("rocketui/" + path).c_str(), "r", "GAME");
}

void RocketFilesystem::Close(Rml::FileHandle file)
{
	g_pFullFileSystem->Close((FileHandle_t)file);
}

size_t RocketFilesystem::Read(void *buffer, size_t size, Rml::FileHandle file)
{
	return g_pFullFileSystem->Read(buffer, size, (FileHandle_t)file);
}

bool RocketFilesystem::Seek(Rml::FileHandle file, long offset, int origin)
{
	g_pFullFileSystem->Seek((FileHandle_t)file, offset, (FileSystemSeek_t)origin);
	return true;
}

size_t RocketFilesystem::Tell(Rml::FileHandle file)
{
	return g_pFullFileSystem->Tell((FileHandle_t)file);
}

size_t RocketFilesystem::Length(Rml::FileHandle file)
{
	return g_pFullFileSystem->Size((FileHandle_t)file);
}