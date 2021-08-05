// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// ( $AMBIENTREFLECTION == 0 ) && ( $USEBOUNCECOLOR == 1 )
// ( $BASEALPHAENVMASK == 1 ) && ( $ENVMAP == 0 )
// ( $BUMPALPHAENVMASK == 1 ) && ( $ENVMAP == 0 )
// ( $BASEALPHAENVMASK == 1 ) && ( $BUMPALPHAENVMASK == 1 )
// ( $BASEALPHASELFILLUMMASK == 1) && ( $BASEALPHAENVMASK == 1 )
// ( $BASEALPHASELFILLUMMASK == 1) && ( $BASEALPHAPHONGMASK == 1 )
// ( $BASEALPHAENVMASK == 1 ) && ( $BASEALPHASELFILLUMMASK )
// ( $FLASHLIGHTDEPTHFILTERMODE > 0 ) && ( $FLASHLIGHT == 0 )
// ( $FLASHLIGHT == 1 ) && ( $FAKERIM == 1 )
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

#ifndef CHARACTER_PS20B_H
#define CHARACTER_PS20B_H

#include "shaderapi/ishaderapi.h"
#include "shaderapi/ishadershadow.h"
#include "materialsystem/imaterialvar.h"

class character_ps20b_Static_Index
{
	unsigned int m_nMASKS1 : 2;
	unsigned int m_nMASKS2 : 2;
	unsigned int m_nFRESNELRANGESTEXTURE : 2;
	unsigned int m_nENVMAP : 2;
	unsigned int m_nAMBIENTREFLECTION : 2;
	unsigned int m_nBASEALPHAENVMASK : 2;
	unsigned int m_nBUMPALPHAENVMASK : 2;
	unsigned int m_nBASEALPHASELFILLUMMASK : 2;
	unsigned int m_nFAKERIM : 2;
	unsigned int m_nFLASHLIGHT : 2;
	unsigned int m_nFLASHLIGHTDEPTHFILTERMODE : 3;
#ifdef _DEBUG
	bool m_bMASKS1 : 1;
	bool m_bMASKS2 : 1;
	bool m_bFRESNELRANGESTEXTURE : 1;
	bool m_bENVMAP : 1;
	bool m_bAMBIENTREFLECTION : 1;
	bool m_bBASEALPHAENVMASK : 1;
	bool m_bBUMPALPHAENVMASK : 1;
	bool m_bBASEALPHASELFILLUMMASK : 1;
	bool m_bFAKERIM : 1;
	bool m_bFLASHLIGHT : 1;
	bool m_bFLASHLIGHTDEPTHFILTERMODE : 1;
#endif	// _DEBUG
public:
	void SetMASKS1( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nMASKS1 = i;
#ifdef _DEBUG
		m_bMASKS1 = true;
#endif	// _DEBUG
	}

	void SetMASKS2( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nMASKS2 = i;
#ifdef _DEBUG
		m_bMASKS2 = true;
#endif	// _DEBUG
	}

	void SetFRESNELRANGESTEXTURE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFRESNELRANGESTEXTURE = i;
#ifdef _DEBUG
		m_bFRESNELRANGESTEXTURE = true;
#endif	// _DEBUG
	}

	void SetENVMAP( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nENVMAP = i;
#ifdef _DEBUG
		m_bENVMAP = true;
#endif	// _DEBUG
	}

	void SetAMBIENTREFLECTION( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nAMBIENTREFLECTION = i;
#ifdef _DEBUG
		m_bAMBIENTREFLECTION = true;
#endif	// _DEBUG
	}

	void SetBASEALPHAENVMASK( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nBASEALPHAENVMASK = i;
#ifdef _DEBUG
		m_bBASEALPHAENVMASK = true;
#endif	// _DEBUG
	}

	void SetBUMPALPHAENVMASK( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nBUMPALPHAENVMASK = i;
#ifdef _DEBUG
		m_bBUMPALPHAENVMASK = true;
#endif	// _DEBUG
	}

	void SetBASEALPHASELFILLUMMASK( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nBASEALPHASELFILLUMMASK = i;
#ifdef _DEBUG
		m_bBASEALPHASELFILLUMMASK = true;
#endif	// _DEBUG
	}

	void SetFAKERIM( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFAKERIM = i;
#ifdef _DEBUG
		m_bFAKERIM = true;
#endif	// _DEBUG
	}

	void SetFLASHLIGHT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFLASHLIGHT = i;
#ifdef _DEBUG
		m_bFLASHLIGHT = true;
#endif	// _DEBUG
	}

	void SetFLASHLIGHTDEPTHFILTERMODE( int i )
	{
		Assert( i >= 0 && i <= 3 );
		m_nFLASHLIGHTDEPTHFILTERMODE = i;
#ifdef _DEBUG
		m_bFLASHLIGHTDEPTHFILTERMODE = true;
#endif	// _DEBUG
	}

	character_ps20b_Static_Index( IShaderShadow* pShaderShadow, IMaterialVar** params )
	{
		m_nMASKS1 = 0;
		m_nMASKS2 = 0;
		m_nFRESNELRANGESTEXTURE = 0;
		m_nENVMAP = 0;
		m_nAMBIENTREFLECTION = 0;
		m_nBASEALPHAENVMASK = 0;
		m_nBUMPALPHAENVMASK = 0;
		m_nBASEALPHASELFILLUMMASK = 0;
		m_nFAKERIM = 0;
		m_nFLASHLIGHT = 0;
		m_nFLASHLIGHTDEPTHFILTERMODE = 0;
#ifdef _DEBUG
		m_bMASKS1 = false;
		m_bMASKS2 = false;
		m_bFRESNELRANGESTEXTURE = false;
		m_bENVMAP = false;
		m_bAMBIENTREFLECTION = false;
		m_bBASEALPHAENVMASK = false;
		m_bBUMPALPHAENVMASK = false;
		m_bBASEALPHASELFILLUMMASK = false;
		m_bFAKERIM = false;
		m_bFLASHLIGHT = false;
		m_bFLASHLIGHTDEPTHFILTERMODE = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bMASKS1 && m_bMASKS2 && m_bFRESNELRANGESTEXTURE && m_bENVMAP && m_bAMBIENTREFLECTION && m_bBASEALPHAENVMASK && m_bBUMPALPHAENVMASK && m_bBASEALPHASELFILLUMMASK && m_bFAKERIM && m_bFLASHLIGHT && m_bFLASHLIGHTDEPTHFILTERMODE );
		return ( 20 * m_nMASKS1 ) + ( 40 * m_nMASKS2 ) + ( 80 * m_nFRESNELRANGESTEXTURE ) + ( 160 * m_nENVMAP ) + ( 320 * m_nAMBIENTREFLECTION ) + ( 640 * m_nBASEALPHAENVMASK ) + ( 1280 * m_nBUMPALPHAENVMASK ) + ( 2560 * m_nBASEALPHASELFILLUMMASK ) + ( 5120 * m_nFAKERIM ) + ( 10240 * m_nFLASHLIGHT ) + ( 20480 * m_nFLASHLIGHTDEPTHFILTERMODE ) + 0;
	}
};

#define shaderStaticTest_character_ps20b psh_forgot_to_set_static_MASKS1 + psh_forgot_to_set_static_MASKS2 + psh_forgot_to_set_static_FRESNELRANGESTEXTURE + psh_forgot_to_set_static_ENVMAP + psh_forgot_to_set_static_AMBIENTREFLECTION + psh_forgot_to_set_static_BASEALPHAENVMASK + psh_forgot_to_set_static_BUMPALPHAENVMASK + psh_forgot_to_set_static_BASEALPHASELFILLUMMASK + psh_forgot_to_set_static_FAKERIM + psh_forgot_to_set_static_FLASHLIGHT + psh_forgot_to_set_static_FLASHLIGHTDEPTHFILTERMODE


class character_ps20b_Dynamic_Index
{
	unsigned int m_nNUM_LIGHTS : 3;
	unsigned int m_nWRITE_DEPTH_TO_DESTALPHA : 1;
	unsigned int m_nWRITEWATERFOGTODESTALPHA : 2;
	unsigned int m_nPIXELFOGTYPE : 2;
#ifdef _DEBUG
	bool m_bNUM_LIGHTS : 1;
	bool m_bWRITE_DEPTH_TO_DESTALPHA : 1;
	bool m_bWRITEWATERFOGTODESTALPHA : 1;
	bool m_bPIXELFOGTYPE : 1;
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

	void SetWRITE_DEPTH_TO_DESTALPHA( int i )
	{
		Assert( i >= 0 && i <= 0 );
		m_nWRITE_DEPTH_TO_DESTALPHA = i;
#ifdef _DEBUG
		m_bWRITE_DEPTH_TO_DESTALPHA = true;
#endif	// _DEBUG
	}

	void SetWRITEWATERFOGTODESTALPHA( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nWRITEWATERFOGTODESTALPHA = i;
#ifdef _DEBUG
		m_bWRITEWATERFOGTODESTALPHA = true;
#endif	// _DEBUG
	}

	void SetPIXELFOGTYPE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPIXELFOGTYPE = i;
#ifdef _DEBUG
		m_bPIXELFOGTYPE = true;
#endif	// _DEBUG
	}

	character_ps20b_Dynamic_Index( IShaderDynamicAPI* pShaderAPI )
	{
		m_nNUM_LIGHTS = 0;
		m_nWRITE_DEPTH_TO_DESTALPHA = 0;
		m_nWRITEWATERFOGTODESTALPHA = 0;
		m_nPIXELFOGTYPE = 0;
#ifdef _DEBUG
		m_bNUM_LIGHTS = false;
		m_bWRITE_DEPTH_TO_DESTALPHA = false;
		m_bWRITEWATERFOGTODESTALPHA = false;
		m_bPIXELFOGTYPE = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bNUM_LIGHTS && m_bWRITE_DEPTH_TO_DESTALPHA && m_bWRITEWATERFOGTODESTALPHA && m_bPIXELFOGTYPE );
		return ( 1 * m_nNUM_LIGHTS ) + ( 5 * m_nWRITE_DEPTH_TO_DESTALPHA ) + ( 5 * m_nWRITEWATERFOGTODESTALPHA ) + ( 10 * m_nPIXELFOGTYPE ) + 0;
	}
};

#define shaderDynamicTest_character_ps20b psh_forgot_to_set_dynamic_NUM_LIGHTS + psh_forgot_to_set_dynamic_WRITE_DEPTH_TO_DESTALPHA + psh_forgot_to_set_dynamic_WRITEWATERFOGTODESTALPHA + psh_forgot_to_set_dynamic_PIXELFOGTYPE


#endif	// CHARACTER_PS20B_H