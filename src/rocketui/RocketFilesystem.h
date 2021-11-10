#ifndef ROCKET_FILESYSTEM_H
#define ROCKET_FILESYSTEM_H

#include <RmlUi/Core/FileInterface.h>

class RocketFilesystem : public Rml::FileInterface
{
public:
	static RocketFilesystem m_Instance;
	RocketFilesystem();

	// Opens a file.
	virtual Rml::FileHandle Open(const Rml::String& path) override;

	// Closes a previously opened file.
	virtual void Close(Rml::FileHandle file) override;

	// Reads data from a previously opened file.
	virtual size_t Read(void* buffer, size_t size, Rml::FileHandle file) override;

	// Seeks to a point in a previously opened file.
	virtual bool Seek(Rml::FileHandle file, long offset, int origin) override;

	// Returns the current position of the file pointer.
	virtual size_t Tell(Rml::FileHandle file) override;

	// Returns the length of the file.
	virtual size_t Length(Rml::FileHandle file) override;
};

#endif