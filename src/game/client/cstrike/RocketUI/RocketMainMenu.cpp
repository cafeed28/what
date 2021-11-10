#include "cbase.h"
#include "RocketMainMenu.h"

#ifdef Assert
#undef Assert
#endif

#include <RmlUi/Core.h>

Rml::ElementDocument *RocketMainMenu::m_Instance = nullptr;
bool RocketMainMenu::m_visible = false;
bool RocketMainMenu::m_grabbingInput = false;

RocketMainMenu::RocketMainMenu() {}

void RocketMainMenu::LoadDialog()
{
	if (!m_Instance)
	{
		m_Instance = g_pRocketUI->LoadDocumentFile(ROCKET_CONTEXT_MENU, "menu.rml", RocketMainMenu::LoadDialog, RocketMainMenu::UnloadDialog);
		m_Instance->Show();
		if (!m_grabbingInput)
		{
			g_pRocketUI->DenyInputToGame(true, "MainMenu");
			m_grabbingInput = true;
		}
		if (!m_Instance)
		{
			Error("Couldn't create RocketUI menu!\n");
			/* Exit */
		}
	}
}

void RocketMainMenu::UnloadDialog()
{
	if (m_Instance)
	{
		m_Instance->Close();
		m_Instance = nullptr;
		if (m_grabbingInput)
		{
			g_pRocketUI->DenyInputToGame(false, "MainMenu");
			m_grabbingInput = false;
		}
	}
}

void RocketMainMenu::UpdateDialog()
{
	// I dont think this is needed here..
	//if( m_Instance )
	//    m_Instance->UpdateDocument()
}

void RocketMainMenu::ShowPanel(bool bShow, bool immediate)
{
	// oh yeah buddy this'll get called before the loading sometimes
	// so if it does, load it for the caller.
	if (bShow)
	{
		if (!m_Instance)
			LoadDialog();

		m_Instance->Show();

		if (!m_grabbingInput)
		{
			g_pRocketUI->DenyInputToGame(true, "MainMenu");
			m_grabbingInput = true;
		}
	}
	else
	{
		if (m_Instance)
			m_Instance->Hide();

		if (m_grabbingInput)
		{
			g_pRocketUI->DenyInputToGame(false, "MainMenu");
			m_grabbingInput = false;
		}
	}

	m_visible = bShow;
}