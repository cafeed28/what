// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// ( $HIGHLIGHT == 1 )
// ( $HIGHLIGHT > 0 ) && ( $THIRDPERSON == 1 )
// ( $HIGHLIGHT > 0 ) && ( $PEEL == 1 )
// ( $PEEL == 1 ) && ( $THIRDPERSON == 1 )
// ( $ALPHAMASK == 1 ) && ( $THIRDPERSON == 1 )
// ( $ALPHAMASK == 1 ) && ( $HIGHLIGHT == 1 )
// ( $ALPHAMASK == 1 ) && ( $PEEL == 1 )
// defined $HDRTYPE && defined $HDRENABLED && !$HDRTYPE && $HDRENABLED
// defined $PIXELFOGTYPE && defined $WRITEWATERFOGTODESTALPHA && ( $PIXELFOGTYPE != 1 ) && $WRITEWATERFOGTODESTALPHA
// defined $LIGHTING_PREVIEW && defined $HDRTYPE && $LIGHTING_PREVIEW && $HDRTYPE != 0
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPTINT && $LIGHTING_PREVIEW && $FASTPATHENVMAPTINT
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPCONTRAST && $LIGHTING_PREVIEW && $FASTPATHENVMAPCONTRAST
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH
// ($FLASHLIGHT || $FLASHLIGHTSHADOWS) && $LIGHTING_PREVIEW
// defined $HDRTYPE && defined $HDRENABLED && !$HDRTYPE && $HDRENABLED
// defined $PIXELFOGTYPE && defined $WRITEWATERFOGTODESTALPHA && ( $PIXELFOGTYPE != 1 ) && $WRITEWATERFOGTODESTALPHA
// defined $LIGHTING_PREVIEW && defined $HDRTYPE && $LIGHTING_PREVIEW && $HDRTYPE != 0
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPTINT && $LIGHTING_PREVIEW && $FASTPATHENVMAPTINT
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPCONTRAST && $LIGHTING_PREVIEW && $FASTPATHENVMAPCONTRAST
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH
// ($FLASHLIGHT || $FLASHLIGHTSHADOWS) && $LIGHTING_PREVIEW

#ifndef WEAPONDECAL_PS30_H
#define WEAPONDECAL_PS30_H

#include "shaderapi/ishaderapi.h"
#include "shaderapi/ishadershadow.h"
#include "materialsystem/imaterialvar.h"

class weapondecal_ps30_Static_Index
{
	unsigned int m_nPHONG : 2;
	unsigned int m_nPHONGEXPONENTTEXTURE : 2;
	unsigned int m_nCUBEMAP : 2;
	unsigned int m_nDECALSTYLE : 3;
	unsigned int m_nTHIRDPERSON : 2;
	unsigned int m_nALPHAMASK : 2;
	unsigned int m_nDESATBASETINT : 2;
#ifdef _DEBUG
	bool m_bPHONG : 1;
	bool m_bPHONGEXPONENTTEXTURE : 1;
	bool m_bCUBEMAP : 1;
	bool m_bDECALSTYLE : 1;
	bool m_bTHIRDPERSON : 1;
	bool m_bALPHAMASK : 1;
	bool m_bDESATBASETINT : 1;
#endif	// _DEBUG
public:
	void SetPHONG( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPHONG = i;
#ifdef _DEBUG
		m_bPHONG = true;
#endif	// _DEBUG
	}

	void SetPHONGEXPONENTTEXTURE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPHONGEXPONENTTEXTURE = i;
#ifdef _DEBUG
		m_bPHONGEXPONENTTEXTURE = true;
#endif	// _DEBUG
	}

	void SetCUBEMAP( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCUBEMAP = i;
#ifdef _DEBUG
		m_bCUBEMAP = true;
#endif	// _DEBUG
	}

	void SetDECALSTYLE( int i )
	{
		Assert( i >= 0 && i <= 5 );
		m_nDECALSTYLE = i;
#ifdef _DEBUG
		m_bDECALSTYLE = true;
#endif	// _DEBUG
	}

	void SetTHIRDPERSON( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nTHIRDPERSON = i;
#ifdef _DEBUG
		m_bTHIRDPERSON = true;
#endif	// _DEBUG
	}

	void SetALPHAMASK( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nALPHAMASK = i;
#ifdef _DEBUG
		m_bALPHAMASK = true;
#endif	// _DEBUG
	}

	void SetDESATBASETINT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nDESATBASETINT = i;
#ifdef _DEBUG
		m_bDESATBASETINT = true;
#endif	// _DEBUG
	}

	weapondecal_ps30_Static_Index( IShaderShadow* pShaderShadow, IMaterialVar** params )
	{
		m_nPHONG = 0;
		m_nPHONGEXPONENTTEXTURE = 0;
		m_nCUBEMAP = 0;
		m_nDECALSTYLE = 0;
		m_nTHIRDPERSON = 0;
		m_nALPHAMASK = 0;
		m_nDESATBASETINT = 0;
#ifdef _DEBUG
		m_bPHONG = false;
		m_bPHONGEXPONENTTEXTURE = false;
		m_bCUBEMAP = false;
		m_bDECALSTYLE = false;
		m_bTHIRDPERSON = false;
		m_bALPHAMASK = false;
		m_bDESATBASETINT = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bPHONG && m_bPHONGEXPONENTTEXTURE && m_bCUBEMAP && m_bDECALSTYLE && m_bTHIRDPERSON && m_bALPHAMASK && m_bDESATBASETINT );
		return ( 30 * m_nPHONG ) + ( 60 * m_nPHONGEXPONENTTEXTURE ) + ( 120 * m_nCUBEMAP ) + ( 240 * m_nDECALSTYLE ) + ( 1440 * m_nTHIRDPERSON ) + ( 2880 * m_nALPHAMASK ) + ( 5760 * m_nDESATBASETINT ) + 0;
	}
};

#define shaderStaticTest_weapondecal_ps30 psh_forgot_to_set_static_PHONG + psh_forgot_to_set_static_PHONGEXPONENTTEXTURE + psh_forgot_to_set_static_CUBEMAP + psh_forgot_to_set_static_DECALSTYLE + psh_forgot_to_set_static_THIRDPERSON + psh_forgot_to_set_static_ALPHAMASK + psh_forgot_to_set_static_DESATBASETINT


class weapondecal_ps30_Dynamic_Index
{
	unsigned int m_nNUM_LIGHTS : 3;
	unsigned int m_nHIGHLIGHT : 2;
	unsigned int m_nPEEL : 2;
#ifdef _DEBUG
	bool m_bNUM_LIGHTS : 1;
	bool m_bHIGHLIGHT : 1;
	bool m_bPEEL : 1;
#endif	// _DEBUG
public:
	void SetNUM_LIGHTS( int i )
	{
		Assert( i >= 0 && i <= 4 );
		m_nNUM_LIGHTS = i;
#ifdef _DEBUG
		m_bNUM_LIGHTS = true;
#endif	// _DEBUG
	}

	void SetHIGHLIGHT( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nHIGHLIGHT = i;
#ifdef _DEBUG
		m_bHIGHLIGHT = true;
#endif	// _DEBUG
	}

	void SetPEEL( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPEEL = i;
#ifdef _DEBUG
		m_bPEEL = true;
#endif	// _DEBUG
	}

	weapondecal_ps30_Dynamic_Index( IShaderDynamicAPI* pShaderAPI )
	{
		m_nNUM_LIGHTS = 0;
		m_nHIGHLIGHT = 0;
		m_nPEEL = 0;
#ifdef _DEBUG
		m_bNUM_LIGHTS = false;
		m_bHIGHLIGHT = false;
		m_bPEEL = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bNUM_LIGHTS && m_bHIGHLIGHT && m_bPEEL );
		return ( 1 * m_nNUM_LIGHTS ) + ( 5 * m_nHIGHLIGHT ) + ( 15 * m_nPEEL ) + 0;
	}
};

#define shaderDynamicTest_weapondecal_ps30 psh_forgot_to_set_dynamic_NUM_LIGHTS + psh_forgot_to_set_dynamic_HIGHLIGHT + psh_forgot_to_set_dynamic_PEEL


#endif	// WEAPONDECAL_PS30_H