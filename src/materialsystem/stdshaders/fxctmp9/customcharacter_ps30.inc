#include "shaderlib/cshader.h"
class customcharacter_ps30_Static_Index
{
private:
	int m_nGENERATEBASETEXTURE;
#ifdef _DEBUG
	bool m_bGENERATEBASETEXTURE;
#endif
public:
	void SetGENERATEBASETEXTURE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nGENERATEBASETEXTURE = i;
#ifdef _DEBUG
		m_bGENERATEBASETEXTURE = true;
#endif
	}
	void SetGENERATEBASETEXTURE( bool i )
	{
		m_nGENERATEBASETEXTURE = i ? 1 : 0;
#ifdef _DEBUG
		m_bGENERATEBASETEXTURE = true;
#endif
	}
private:
	int m_nGENERATENORMAL;
#ifdef _DEBUG
	bool m_bGENERATENORMAL;
#endif
public:
	void SetGENERATENORMAL( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nGENERATENORMAL = i;
#ifdef _DEBUG
		m_bGENERATENORMAL = true;
#endif
	}
	void SetGENERATENORMAL( bool i )
	{
		m_nGENERATENORMAL = i ? 1 : 0;
#ifdef _DEBUG
		m_bGENERATENORMAL = true;
#endif
	}
private:
	int m_nGENERATEMASKS1;
#ifdef _DEBUG
	bool m_bGENERATEMASKS1;
#endif
public:
	void SetGENERATEMASKS1( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nGENERATEMASKS1 = i;
#ifdef _DEBUG
		m_bGENERATEMASKS1 = true;
#endif
	}
	void SetGENERATEMASKS1( bool i )
	{
		m_nGENERATEMASKS1 = i ? 1 : 0;
#ifdef _DEBUG
		m_bGENERATEMASKS1 = true;
#endif
	}
private:
	int m_nCHEAPFILTERING;
#ifdef _DEBUG
	bool m_bCHEAPFILTERING;
#endif
public:
	void SetCHEAPFILTERING( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nCHEAPFILTERING = i;
#ifdef _DEBUG
		m_bCHEAPFILTERING = true;
#endif
	}
	void SetCHEAPFILTERING( bool i )
	{
		m_nCHEAPFILTERING = i ? 1 : 0;
#ifdef _DEBUG
		m_bCHEAPFILTERING = true;
#endif
	}
private:
	int m_nBASEALPHAPHONGMASK;
#ifdef _DEBUG
	bool m_bBASEALPHAPHONGMASK;
#endif
public:
	void SetBASEALPHAPHONGMASK( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nBASEALPHAPHONGMASK = i;
#ifdef _DEBUG
		m_bBASEALPHAPHONGMASK = true;
#endif
	}
	void SetBASEALPHAPHONGMASK( bool i )
	{
		m_nBASEALPHAPHONGMASK = i ? 1 : 0;
#ifdef _DEBUG
		m_bBASEALPHAPHONGMASK = true;
#endif
	}
private:
	int m_nBASEALPHAENVMASK;
#ifdef _DEBUG
	bool m_bBASEALPHAENVMASK;
#endif
public:
	void SetBASEALPHAENVMASK( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nBASEALPHAENVMASK = i;
#ifdef _DEBUG
		m_bBASEALPHAENVMASK = true;
#endif
	}
	void SetBASEALPHAENVMASK( bool i )
	{
		m_nBASEALPHAENVMASK = i ? 1 : 0;
#ifdef _DEBUG
		m_bBASEALPHAENVMASK = true;
#endif
	}
private:
	int m_nBUMPALPHAENVMASK;
#ifdef _DEBUG
	bool m_bBUMPALPHAENVMASK;
#endif
public:
	void SetBUMPALPHAENVMASK( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nBUMPALPHAENVMASK = i;
#ifdef _DEBUG
		m_bBUMPALPHAENVMASK = true;
#endif
	}
	void SetBUMPALPHAENVMASK( bool i )
	{
		m_nBUMPALPHAENVMASK = i ? 1 : 0;
#ifdef _DEBUG
		m_bBUMPALPHAENVMASK = true;
#endif
	}
private:
	int m_nUSEPATTERN;
#ifdef _DEBUG
	bool m_bUSEPATTERN;
#endif
public:
	void SetUSEPATTERN( int i )
	{
		Assert( i >= 0 && i <= 4 );
		m_nUSEPATTERN = i;
#ifdef _DEBUG
		m_bUSEPATTERN = true;
#endif
	}
	void SetUSEPATTERN( bool i )
	{
		m_nUSEPATTERN = i ? 1 : 0;
#ifdef _DEBUG
		m_bUSEPATTERN = true;
#endif
	}
public:
	customcharacter_ps30_Static_Index( )
	{
#ifdef _DEBUG
		m_bGENERATEBASETEXTURE = false;
#endif // _DEBUG
		m_nGENERATEBASETEXTURE = 0;
#ifdef _DEBUG
		m_bGENERATENORMAL = false;
#endif // _DEBUG
		m_nGENERATENORMAL = 0;
#ifdef _DEBUG
		m_bGENERATEMASKS1 = false;
#endif // _DEBUG
		m_nGENERATEMASKS1 = 0;
#ifdef _DEBUG
		m_bCHEAPFILTERING = false;
#endif // _DEBUG
		m_nCHEAPFILTERING = 0;
#ifdef _DEBUG
		m_bBASEALPHAPHONGMASK = false;
#endif // _DEBUG
		m_nBASEALPHAPHONGMASK = 0;
#ifdef _DEBUG
		m_bBASEALPHAENVMASK = false;
#endif // _DEBUG
		m_nBASEALPHAENVMASK = 0;
#ifdef _DEBUG
		m_bBUMPALPHAENVMASK = false;
#endif // _DEBUG
		m_nBUMPALPHAENVMASK = 0;
#ifdef _DEBUG
		m_bUSEPATTERN = false;
#endif // _DEBUG
		m_nUSEPATTERN = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bGENERATEBASETEXTURE && m_bGENERATENORMAL && m_bGENERATEMASKS1 && m_bCHEAPFILTERING && m_bBASEALPHAPHONGMASK && m_bBASEALPHAENVMASK && m_bBUMPALPHAENVMASK && m_bUSEPATTERN;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nGENERATEBASETEXTURE ) + ( 2 * m_nGENERATENORMAL ) + ( 4 * m_nGENERATEMASKS1 ) + ( 8 * m_nCHEAPFILTERING ) + ( 16 * m_nBASEALPHAPHONGMASK ) + ( 32 * m_nBASEALPHAENVMASK ) + ( 64 * m_nBUMPALPHAENVMASK ) + ( 128 * m_nUSEPATTERN ) + 0;
	}
};
#define shaderStaticTest_customcharacter_ps30 psh_forgot_to_set_static_GENERATEBASETEXTURE + psh_forgot_to_set_static_GENERATENORMAL + psh_forgot_to_set_static_GENERATEMASKS1 + psh_forgot_to_set_static_CHEAPFILTERING + psh_forgot_to_set_static_BASEALPHAPHONGMASK + psh_forgot_to_set_static_BASEALPHAENVMASK + psh_forgot_to_set_static_BUMPALPHAENVMASK + psh_forgot_to_set_static_USEPATTERN + 0
class customcharacter_ps30_Dynamic_Index
{
public:
	customcharacter_ps30_Dynamic_Index()
	{
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
#endif // _DEBUG
		return 0;
	}
};
#define shaderDynamicTest_customcharacter_ps30 0
