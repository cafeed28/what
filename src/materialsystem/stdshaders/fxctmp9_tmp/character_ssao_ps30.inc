#include "shaderlib/cshader.h"
class character_ssao_ps30_Static_Index
{
private:
	int m_nQUALITY_MODE;
#ifdef _DEBUG
	bool m_bQUALITY_MODE;
#endif
public:
	void SetQUALITY_MODE( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nQUALITY_MODE = i;
#ifdef _DEBUG
		m_bQUALITY_MODE = true;
#endif
	}
	void SetQUALITY_MODE( bool i )
	{
		m_nQUALITY_MODE = i ? 1 : 0;
#ifdef _DEBUG
		m_bQUALITY_MODE = true;
#endif
	}
public:
	character_ssao_ps30_Static_Index( )
	{
#ifdef _DEBUG
		m_bQUALITY_MODE = false;
#endif // _DEBUG
		m_nQUALITY_MODE = 0;
	}
	int GetIndex()
	{
		// Asserts to make sure that we aren't using any skipped combinations.
		// Asserts to make sure that we are setting all of the combination vars.
#ifdef _DEBUG
		bool bAllStaticVarsDefined = m_bQUALITY_MODE;
		Assert( bAllStaticVarsDefined );
#endif // _DEBUG
		return ( 1 * m_nQUALITY_MODE ) + 0;
	}
};
#define shaderStaticTest_character_ssao_ps30 psh_forgot_to_set_static_QUALITY_MODE + 0
class character_ssao_ps30_Dynamic_Index
{
public:
	character_ssao_ps30_Dynamic_Index()
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
#define shaderDynamicTest_character_ssao_ps30 0
