//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
 //====== Copyright © 1996-2003, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#include "cbase.h"
#include "hudelement.h"
#include <vgui_controls/Panel.h>
#include <vgui/ISurface.h>
#include "clientmode_csnormal.h"
#include "cs_gamerules.h"
#include "hud_numericdisplay.h"

extern ConVar hud_healtharmor_style;

class CHudArmor : public CHudElement, public CHudNumericDisplay
{
public:
	DECLARE_CLASS_SIMPLE( CHudArmor, CHudNumericDisplay );

	CHudArmor( const char *name );

	virtual bool ShouldDraw();	
	virtual void Paint();
	virtual void Init();
	virtual void OnThink();
	virtual void ApplySchemeSettings( IScheme *scheme );

private:
	CHudTexture *m_pArmorIcon;
	CHudTexture *m_pArmor_HelmetIcon;

	CPanelAnimationVarAliasType( float, icon_xpos, "icon_xpos", "0", "proportional_float" );
	CPanelAnimationVarAliasType( float, icon_ypos, "icon_ypos", "2", "proportional_float" );

	CPanelAnimationVarAliasType( int, legacy_xpos, "legacy_xpos", "0", "proportional_xpos" );
	CPanelAnimationVarAliasType( int, legacy_ypos, "legacy_ypos", "0", "proportional_ypos" );
	CPanelAnimationVarAliasType( int, legacy_wide, "legacy_wide", "0", "proportional_width" );
	CPanelAnimationVarAliasType( int, legacy_tall, "legacy_tall", "0", "proportional_height" );

	CPanelAnimationVarAliasType( int, simple_xpos, "simple_xpos", "0", "proportional_xpos" );
	CPanelAnimationVarAliasType( int, simple_ypos, "simple_ypos", "0", "proportional_ypos" );
	CPanelAnimationVarAliasType( int, simple_wide, "simple_wide", "0", "proportional_width" );
	CPanelAnimationVarAliasType( int, simple_tall, "simple_tall", "0", "proportional_height" );

	CPanelAnimationVarAliasType( float, progress_xpos, "progress_xpos", "0", "proportional_float" );
	CPanelAnimationVarAliasType( float, progress_ypos, "progress_ypos", "0", "proportional_float" );
	CPanelAnimationVarAliasType( float, progress_wide, "progress_wide", "0", "proportional_float" );
	CPanelAnimationVarAliasType( float, progress_tall, "progress_tall", "0", "proportional_float" );
	CPanelAnimationVarAliasType(float, progress_chuck_wide, "progress_chuck_wide", "2", "proportional_float");
	CPanelAnimationVarAliasType(float, progress_chuck_gap, "progress_chuck_gap", "0", "proportional_float");

	CPanelAnimationVar(Color, m_ProgressFgColor, "ProgressFgColor", "FgColor");
	CPanelAnimationVar(Color, m_ProgressBgColor, "ProgressBgColor", "BgColor");
	CPanelAnimationVar(int, m_ProgressColorAlpha, "ProgressColorAlpha", "0");;

	int m_iStyle;
	int m_iOriginalXPos;
	int m_iOriginalYPos;
	int m_iOriginalWide;
	int m_iOriginalTall;

	float icon_wide;
	float icon_tall;
};


DECLARE_HUDELEMENT( CHudArmor );


CHudArmor::CHudArmor( const char *pName ) : CHudNumericDisplay( NULL, "HudArmor" ), CHudElement( pName )
{
	SetHiddenBits( HIDEHUD_HEALTH | HIDEHUD_PLAYERDEAD );

	m_iStyle = -1;
	m_iOriginalXPos = 0;
	m_iOriginalYPos = 0;
	m_iOriginalWide = 0;
	m_iOriginalTall = 0;
}


void CHudArmor::Init()
{
	SetIndent( true );
}

void CHudArmor::ApplySchemeSettings( IScheme *scheme )
{
	BaseClass::ApplySchemeSettings( scheme );

	if( !m_pArmorIcon )
	{
		m_pArmorIcon = gHUD.GetIcon( "shield_bright" );
	}

	if( !m_pArmor_HelmetIcon )
	{
		m_pArmor_HelmetIcon = gHUD.GetIcon( "shield_kevlar_bright" );
	}	

	if( m_pArmorIcon )
	{
		icon_tall = GetTall() - YRES(2);
		float scale = icon_tall / (float)m_pArmorIcon->Height();
		icon_wide = ( scale ) * (float)m_pArmorIcon->Width();
	}

	GetBounds( m_iOriginalXPos, m_iOriginalYPos, m_iOriginalWide, m_iOriginalTall );
}


bool CHudArmor::ShouldDraw()
{
	C_CSPlayer *pPlayer = C_CSPlayer::GetLocalCSPlayer();
	if ( pPlayer )
	{
		return !pPlayer->IsObserver();
	}
	else
	{
		return false;
	}
}


void CHudArmor::Paint()
{
	// Update the time.
	C_CSPlayer *pPlayer = C_CSPlayer::GetLocalCSPlayer();
	if ( pPlayer )
	{
		int iArmorValue = pPlayer->ArmorValue();
		if( pPlayer->HasHelmet() && iArmorValue > 0 )
		{
			if( m_pArmor_HelmetIcon )
			{
				m_pArmor_HelmetIcon->DrawSelf( icon_xpos, icon_ypos, icon_wide, icon_tall, GetFgColor() );
			}
		}
		else
		{
			if( m_pArmorIcon )
			{
				m_pArmorIcon->DrawSelf( icon_xpos, icon_ypos, icon_wide, icon_tall, GetFgColor() );
			}
		}

		if ( hud_healtharmor_style.GetInt() == HUD_STYLE_DEFAULT )
		{
			int chunkCount = progress_wide / (progress_chuck_wide + progress_chuck_gap);
			int enabledChunks = (int)((float)chunkCount * (iArmorValue / 100.0f) + .5f);

			// draw the progress bar
			surface()->DrawSetColor(m_ProgressFgColor);

			int xpos = progress_xpos, ypos = progress_ypos;

			for (int i = 0; i < enabledChunks; i++)
			{
				surface()->DrawFilledRect(xpos, ypos, xpos + progress_chuck_wide, ypos + progress_tall);
				xpos += (progress_chuck_wide + progress_chuck_gap);
			}

			// Draw the exhausted bar.
			// if ProgressColorAlpha exsist, use Alpha
			if (m_ProgressColorAlpha > 0)
				surface()->DrawSetColor(Color(m_ProgressFgColor[0], m_ProgressFgColor[1], m_ProgressFgColor[2], m_ProgressColorAlpha));
			else
				surface()->DrawSetColor(m_ProgressBgColor);

			for (int i = enabledChunks; i < chunkCount; i++)
			{
				surface()->DrawFilledRect(xpos, ypos, xpos + progress_chuck_wide, ypos + progress_tall);
				xpos += (progress_chuck_wide + progress_chuck_gap);
			}
		}

		SetDisplayValue( iArmorValue );
		SetShouldDisplayValue( true );
		BaseClass::Paint();
	}
}

void CHudArmor::OnThink()
{
	if ( m_iStyle != hud_healtharmor_style.GetInt() )
	{
		m_iStyle = hud_healtharmor_style.GetInt();

		switch ( m_iStyle )
		{
			case HUD_STYLE_DEFAULT:
				SetBounds( m_iOriginalXPos, m_iOriginalYPos, m_iOriginalWide, m_iOriginalTall );
				break;

			case HUD_STYLE_SIMPLE:
				SetBounds( simple_xpos, simple_ypos, simple_wide, simple_tall );
				break;

			case HUD_STYLE_LEGACY:
				SetBounds( legacy_xpos, legacy_ypos, legacy_wide, legacy_tall );
				break;
		}
	}
}

