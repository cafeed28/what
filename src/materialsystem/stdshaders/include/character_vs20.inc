// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// ( $FLATTEN_STATIC_CONTROL_FLOW == 0 ) && ( $NUM_LIGHTS > 0 )
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH

#ifndef CHARACTER_VS20_H
#define CHARACTER_VS20_H

#include "shaderapi/ishaderapi.h"
#include "shaderapi/ishadershadow.h"
#include "materialsystem/imaterialvar.h"

class character_vs20_Static_Index
{
	unsigned int m_nUSEBOUNCECOLOR : 1;
	unsigned int m_nFLASHLIGHT : 2;
	unsigned int m_nFLATTEN_STATIC_CONTROL_FLOW : 2;
#ifdef _DEBUG
	bool m_bUSEBOUNCECOLOR : 1;
	bool m_bFLASHLIGHT : 1;
	bool m_bFLATTEN_STATIC_CONTROL_FLOW : 1;
#endif	// _DEBUG
public:
	void SetUSEBOUNCECOLOR( int i )
	{
		Assert( i >= 0 && i <= 0 );
		m_nUSEBOUNCECOLOR = i;
#ifdef _DEBUG
		m_bUSEBOUNCECOLOR = true;
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

	void SetFLATTEN_STATIC_CONTROL_FLOW( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nFLATTEN_STATIC_CONTROL_FLOW = i;
#ifdef _DEBUG
		m_bFLATTEN_STATIC_CONTROL_FLOW = true;
#endif	// _DEBUG
	}

	character_vs20_Static_Index( IShaderShadow* pShaderShadow, IMaterialVar** params )
	{
		m_nUSEBOUNCECOLOR = 0;
		m_nFLASHLIGHT = 0;
		m_nFLATTEN_STATIC_CONTROL_FLOW = 0;
#ifdef _DEBUG
		m_bUSEBOUNCECOLOR = false;
		m_bFLASHLIGHT = false;
		m_bFLATTEN_STATIC_CONTROL_FLOW = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bUSEBOUNCECOLOR && m_bFLASHLIGHT && m_bFLATTEN_STATIC_CONTROL_FLOW );
		return ( 12 * m_nUSEBOUNCECOLOR ) + ( 12 * m_nFLASHLIGHT ) + ( 24 * m_nFLATTEN_STATIC_CONTROL_FLOW ) + 0;
	}
};

#define shaderStaticTest_character_vs20 vsh_forgot_to_set_static_USEBOUNCECOLOR + vsh_forgot_to_set_static_FLASHLIGHT + vsh_forgot_to_set_static_FLATTEN_STATIC_CONTROL_FLOW


class character_vs20_Dynamic_Index
{
	unsigned int m_nCOMPRESSED_VERTS : 2;
	unsigned int m_nSKINNING : 2;
	unsigned int m_nNUM_LIGHTS : 2;
#ifdef _DEBUG
	bool m_bCOMPRESSED_VERTS : 1;
	bool m_bSKINNING : 1;
	bool m_bNUM_LIGHTS : 1;
#endif	// _DEBUG
public:
	void SetCOMPRESSED_VERTS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCOMPRESSED_VERTS = i;
#ifdef _DEBUG
		m_bCOMPRESSED_VERTS = true;
#endif	// _DEBUG
	}

	void SetSKINNING( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSKINNING = i;
#ifdef _DEBUG
		m_bSKINNING = true;
#endif	// _DEBUG
	}

	void SetNUM_LIGHTS( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nNUM_LIGHTS = i;
#ifdef _DEBUG
		m_bNUM_LIGHTS = true;
#endif	// _DEBUG
	}

	character_vs20_Dynamic_Index( IShaderDynamicAPI* pShaderAPI )
	{
		m_nCOMPRESSED_VERTS = 0;
		m_nSKINNING = 0;
		m_nNUM_LIGHTS = 0;
#ifdef _DEBUG
		m_bCOMPRESSED_VERTS = false;
		m_bSKINNING = false;
		m_bNUM_LIGHTS = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bCOMPRESSED_VERTS && m_bSKINNING && m_bNUM_LIGHTS );
		return ( 1 * m_nCOMPRESSED_VERTS ) + ( 2 * m_nSKINNING ) + ( 4 * m_nNUM_LIGHTS ) + 0;
	}
};

#define shaderDynamicTest_character_vs20 vsh_forgot_to_set_dynamic_COMPRESSED_VERTS + vsh_forgot_to_set_dynamic_SKINNING + vsh_forgot_to_set_dynamic_NUM_LIGHTS


#endif	// CHARACTER_VS20_H