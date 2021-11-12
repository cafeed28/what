#include "RocketSystem.h"

#include <windows.h>

#include <tier3/tier3.h>
#include "../engine/igame.h"
#include "vgui/ISystem.h"
#include "vgui/Cursor.h"

#include "RocketUIImpl.h"

RocketSystem RocketSystem::m_Instance;

//extern IGame* game;
IGame* game = 0;

double RocketSystem::GetElapsedTime()
{
	return (double)RocketUIImpl::m_Instance.GetTime();
}

bool RocketSystem::LogMessage(Rml::Log::Type type, const Rml::String &message)
{
	switch (type) {
	case Rml::Log::LT_ERROR:
		Error("[RocketUI]%s\n", message.c_str());
		return true;

	case Rml::Log::LT_WARNING:
		Warning("[RocketUI]%s\n", message.c_str());
		return false;

	default:
		Msg("[RocketUI]%s\n", message.c_str());
		return false;
	}
}

void RocketSystem::SetMouseCursor(const Rml::String &cursor_name)
{
	HWND hWnd = (HWND)game->GetMainWindow();

	HCURSOR cursor = nullptr;

	if (cursor_name.empty() || cursor_name == "arrow")
		cursor = LoadCursor(nullptr, IDC_ARROW);
	else if (cursor_name == "move")
		cursor = LoadCursor(nullptr, IDC_SIZEALL);
	else if (cursor_name == "pointer")
		cursor = LoadCursor(nullptr, IDC_HAND);
	else if (cursor_name == "resize")
		cursor = LoadCursor(nullptr, IDC_SIZENWSE);
	else if (cursor_name == "cross")
		cursor = LoadCursor(nullptr, IDC_CROSS);
	else if (cursor_name == "text")
		cursor = LoadCursor(nullptr, IDC_IBEAM);
	else if (cursor_name == "unavailable")
		cursor = LoadCursor(nullptr, IDC_NO);

	if (!cursor) return;

	SetCursor(cursor);
	SetClassLongPtrA(hWnd, GCLP_HCURSOR, (LONG_PTR)cursor);
}

void RocketSystem::SetClipboardText(const Rml::String& text)
{
	g_pVGuiSystem->SetClipboardText(text.c_str(), text.size());
}

void RocketSystem::GetClipboardText(Rml::String& text)
{
	char buffer[1024];
	g_pVGuiSystem->GetClipboardText(0, buffer, sizeof(buffer));
	text.copy(buffer, sizeof(buffer));
}