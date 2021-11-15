#ifndef ROCKET_SYSTEM_H
#define ROCKET_SYSTEM_H

#include <RmlUi/Core/SystemInterface.h>

class RocketSystem : public Rml::SystemInterface
{
private:
	void* m_hWnd;

public:
	static RocketSystem m_Instance;

	// Get the number of seconds elapsed since the start of the application.
	double GetElapsedTime() override;

	// Log the specified message.
	virtual bool LogMessage(Rml::Log::Type type, const Rml::String& message) override;

	// Set mouse cursor.
	void SetMouseCursor(const Rml::String& cursor_name) override;

	// Set clipboard text.
	void SetClipboardText(const Rml::String& text) override;

	// Get clipboard text.
	void GetClipboardText(Rml::String& text) override;

	inline void SetHWnd(void* hWnd)
	{
		m_hWnd = hWnd;
	}
};

#endif