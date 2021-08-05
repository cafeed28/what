// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH

#ifndef WEAPONDECAL_VS20_H
#define WEAPONDECAL_VS20_H

#include "shaderapi/ishaderapi.h"
#include "shaderapi/ishadershadow.h"
#include "materialsystem/imaterialvar.h"

class weapondecal_vs20_Static_Index
{
	unsigned int m_nMIRROR : 2;
	unsigned int m_nNORMALMAP : 2;
#ifdef _DEBUG
	bool m_bMIRROR : 1;
	bool m_bNORMALMAP : 1;
#endif	// _DEBUG
public:
	void SetMIRROR( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nMIRROR = i;
#ifdef _DEBUG
		m_bMIRROR = true;
#endif	// _DEBUG
	}

	void SetNORMALMAP( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nNORMALMAP = i;
#ifdef _DEBUG
		m_bNORMALMAP = true;
#endif	// _DEBUG
	}

	weapondecal_vs20_Static_Index( IShaderShadow* pShaderShadow, IMaterialVar** params )
	{
		m_nMIRROR = 0;
		m_nNORMALMAP = 0;
#ifdef _DEBUG
		m_bMIRROR = false;
		m_bNORMALMAP = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bMIRROR && m_bNORMALMAP );
		return ( 20 * m_nMIRROR ) + ( 40 * m_nNORMALMAP ) + 0;
	}
};

#define shaderStaticTest_weapondecal_vs20 vsh_forgot_to_set_static_MIRROR + vsh_forgot_to_set_static_NORMALMAP


class weapondecal_vs20_Dynamic_Index
{
	unsigned int m_nSKINNING : 2;
	unsigned int m_nCOMPRESSED_VERTS : 2;
	unsigned int m_nNUM_LIGHTS : 3;
#ifdef _DEBUG
	bool m_bSKINNING : 1;
	bool m_bCOMPRESSED_VERTS : 1;
	bool m_bNUM_LIGHTS : 1;
#endif	// _DEBUG
public:
	void SetSKINNING( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSKINNING = i;
#ifdef _DEBUG
		m_bSKINNING = true;
#endif	// _DEBUG
	}

	void SetCOMPRESSED_VERTS( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCOMPRESSED_VERTS = i;
#ifdef _DEBUG
		m_bCOMPRESSED_VERTS = true;
#endif	// _DEBUG
	}

	void SetNUM_LIGHTS( int i )
	{
		Assert( i >= 0 && i <= 4 );
		m_nNUM_LIGHTS = i;
#ifdef _DEBUG
		m_bNUM_LIGHTS = true;
#endif	// _DEBUG
	}

	weapondecal_vs20_Dynamic_Index( IShaderDynamicAPI* pShaderAPI )
	{
		m_nSKINNING = 0;
		m_nCOMPRESSED_VERTS = 0;
		m_nNUM_LIGHTS = 0;
#ifdef _DEBUG
		m_bSKINNING = false;
		m_bCOMPRESSED_VERTS = false;
		m_bNUM_LIGHTS = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bSKINNING && m_bCOMPRESSED_VERTS && m_bNUM_LIGHTS );
		return ( 1 * m_nSKINNING ) + ( 2 * m_nCOMPRESSED_VERTS ) + ( 4 * m_nNUM_LIGHTS ) + 0;
	}
};

#define shaderDynamicTest_weapondecal_vs20 vsh_forgot_to_set_dynamic_SKINNING + vsh_forgot_to_set_dynamic_COMPRESSED_VERTS + vsh_forgot_to_set_dynamic_NUM_LIGHTS


#endif	// WEAPONDECAL_VS20_H