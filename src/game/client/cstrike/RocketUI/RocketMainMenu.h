#ifndef ROCKET_MAIN_MENU
#define ROCKET_MAIN_MENU

#include <rocketui/rocketui.h>

class RocketMainMenu
{
protected:
	static Rml::ElementDocument *m_Instance;

	RocketMainMenu();
public:
	static void LoadDialog(void);
	static void UnloadDialog(void);
	static void RestorePanel(void);
	static void ShowPanel(bool bShow, bool immediate = false);
	static bool IsActive() { return m_Instance != nullptr; }
	static bool IsVisible() { return m_visible; }
	static void UpdateDialog(void);
	static Rml::ElementDocument *GetInstance() { return m_Instance; }
private:
	static bool m_visible;
	static bool m_grabbingInput;
};

#endif