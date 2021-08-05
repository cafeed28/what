// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// ( $PAINTSTYLE == 0 )
// ( ( $CHEAPMODE == 1 ) && !( ( $PAINTSTYLE == 3 ) || ( $PAINTSTYLE == 6 ) ) )
// ( ( $EXPONENTMODE == 1 ) && ( $CHEAPMODE == 1 ) )
// ( ( $NUM_LIGHTS != 0 ) && ( $PREVIEW == 0 ) )
// ( ( $PREVIEW == 0 ) && ( $PREVIEWPHONGALBEDOTINT == 1 ) )
// ( ( $PREVIEW == 1 ) && ( $EXPONENTMODE == 1 ) )
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
// defined $HDRTYPE && defined $HDRENABLED && !$HDRTYPE && $HDRENABLED
// defined $PIXELFOGTYPE && defined $WRITEWATERFOGTODESTALPHA && ( $PIXELFOGTYPE != 1 ) && $WRITEWATERFOGTODESTALPHA
// defined $LIGHTING_PREVIEW && defined $HDRTYPE && $LIGHTING_PREVIEW && $HDRTYPE != 0
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPTINT && $LIGHTING_PREVIEW && $FASTPATHENVMAPTINT
// defined $LIGHTING_PREVIEW && defined $FASTPATHENVMAPCONTRAST && $LIGHTING_PREVIEW && $FASTPATHENVMAPCONTRAST
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH
// ($FLASHLIGHT || $FLASHLIGHTSHADOWS) && $LIGHTING_PREVIEW

#ifndef CUSTOMWEAPON_PS30_H
#define CUSTOMWEAPON_PS30_H

#include "shaderapi/ishaderapi.h"
#include "shaderapi/ishadershadow.h"
#include "materialsystem/imaterialvar.h"

class customweapon_ps30_Static_Index
{
	unsigned int m_nPAINTSTYLE : 4;
	unsigned int m_nEXPONENTMODE : 2;
	unsigned int m_nCHEAPMODE : 2;
	unsigned int m_nPREVIEW : 2;
	unsigned int m_nPREVIEWPHONGALBEDOTINT : 2;
	unsigned int m_nPHONGALBEDOFACTORMODE : 2;
#ifdef _DEBUG
	bool m_bPAINTSTYLE : 1;
	bool m_bEXPONENTMODE : 1;
	bool m_bCHEAPMODE : 1;
	bool m_bPREVIEW : 1;
	bool m_bPREVIEWPHONGALBEDOTINT : 1;
	bool m_bPHONGALBEDOFACTORMODE : 1;
#endif	// _DEBUG
public:
	void SetPAINTSTYLE( int i )
	{
		Assert( i >= 0 && i <= 9 );
		m_nPAINTSTYLE = i;
#ifdef _DEBUG
		m_bPAINTSTYLE = true;
#endif	// _DEBUG
	}

	void SetEXPONENTMODE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nEXPONENTMODE = i;
#ifdef _DEBUG
		m_bEXPONENTMODE = true;
#endif	// _DEBUG
	}

	void SetCHEAPMODE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCHEAPMODE = i;
#ifdef _DEBUG
		m_bCHEAPMODE = true;
#endif	// _DEBUG
	}

	void SetPREVIEW( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPREVIEW = i;
#ifdef _DEBUG
		m_bPREVIEW = true;
#endif	// _DEBUG
	}

	void SetPREVIEWPHONGALBEDOTINT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPREVIEWPHONGALBEDOTINT = i;
#ifdef _DEBUG
		m_bPREVIEWPHONGALBEDOTINT = true;
#endif	// _DEBUG
	}

	void SetPHONGALBEDOFACTORMODE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPHONGALBEDOFACTORMODE = i;
#ifdef _DEBUG
		m_bPHONGALBEDOFACTORMODE = true;
#endif	// _DEBUG
	}

	customweapon_ps30_Static_Index( IShaderShadow* pShaderShadow, IMaterialVar** params )
	{
		m_nPAINTSTYLE = 0;
		m_nEXPONENTMODE = 0;
		m_nCHEAPMODE = 0;
		m_nPREVIEW = 0;
		m_nPREVIEWPHONGALBEDOTINT = 0;
		m_nPHONGALBEDOFACTORMODE = 0;
#ifdef _DEBUG
		m_bPAINTSTYLE = false;
		m_bEXPONENTMODE = false;
		m_bCHEAPMODE = false;
		m_bPREVIEW = false;
		m_bPREVIEWPHONGALBEDOTINT = false;
		m_bPHONGALBEDOFACTORMODE = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bPAINTSTYLE && m_bEXPONENTMODE && m_bCHEAPMODE && m_bPREVIEW && m_bPREVIEWPHONGALBEDOTINT && m_bPHONGALBEDOFACTORMODE );
		return ( 5 * m_nPAINTSTYLE ) + ( 50 * m_nEXPONENTMODE ) + ( 100 * m_nCHEAPMODE ) + ( 200 * m_nPREVIEW ) + ( 400 * m_nPREVIEWPHONGALBEDOTINT ) + ( 800 * m_nPHONGALBEDOFACTORMODE ) + 0;
	}
};

#define shaderStaticTest_customweapon_ps30 psh_forgot_to_set_static_PAINTSTYLE + psh_forgot_to_set_static_EXPONENTMODE + psh_forgot_to_set_static_CHEAPMODE + psh_forgot_to_set_static_PREVIEW + psh_forgot_to_set_static_PREVIEWPHONGALBEDOTINT + psh_forgot_to_set_static_PHONGALBEDOFACTORMODE


class customweapon_ps30_Dynamic_Index
{
	unsigned int m_nNUM_LIGHTS : 3;
#ifdef _DEBUG
	bool m_bNUM_LIGHTS : 1;
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

	customweapon_ps30_Dynamic_Index( IShaderDynamicAPI* pShaderAPI )
	{
		m_nNUM_LIGHTS = 0;
#ifdef _DEBUG
		m_bNUM_LIGHTS = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bNUM_LIGHTS );
		return ( 1 * m_nNUM_LIGHTS ) + 0;
	}
};

#define shaderDynamicTest_customweapon_ps30 psh_forgot_to_set_dynamic_NUM_LIGHTS


#endif	// CUSTOMWEAPON_PS30_H