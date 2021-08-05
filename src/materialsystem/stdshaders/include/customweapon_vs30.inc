// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// ( ( $PREVIEW == 0 ) && ( $SKINNING == 1 ) )
// ( ( $NUM_LIGHTS != 0 ) && ( $PREVIEW == 0 ) )
// defined $LIGHTING_PREVIEW && defined $FASTPATH && $LIGHTING_PREVIEW && $FASTPATH

#ifndef CUSTOMWEAPON_VS30_H
#define CUSTOMWEAPON_VS30_H

#include "shaderapi/ishaderapi.h"
#include "shaderapi/ishadershadow.h"
#include "materialsystem/imaterialvar.h"

class customweapon_vs30_Static_Index
{
	unsigned int m_nPREVIEW : 2;
#ifdef _DEBUG
	bool m_bPREVIEW : 1;
#endif	// _DEBUG
public:
	void SetPREVIEW( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nPREVIEW = i;
#ifdef _DEBUG
		m_bPREVIEW = true;
#endif	// _DEBUG
	}

	customweapon_vs30_Static_Index( IShaderShadow* pShaderShadow, IMaterialVar** params )
	{
		m_nPREVIEW = 0;
#ifdef _DEBUG
		m_bPREVIEW = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bPREVIEW );
		return ( 20 * m_nPREVIEW ) + 0;
	}
};

#define shaderStaticTest_customweapon_vs30 vsh_forgot_to_set_static_PREVIEW


class customweapon_vs30_Dynamic_Index
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

	customweapon_vs30_Dynamic_Index( IShaderDynamicAPI* pShaderAPI )
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

#define shaderDynamicTest_customweapon_vs30 vsh_forgot_to_set_dynamic_SKINNING + vsh_forgot_to_set_dynamic_COMPRESSED_VERTS + vsh_forgot_to_set_dynamic_NUM_LIGHTS


#endif	// CUSTOMWEAPON_VS30_H