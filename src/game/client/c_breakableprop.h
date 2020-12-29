//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef C_BREAKABLEPROP_H
#define C_BREAKABLEPROP_H
#ifdef _WIN32
#pragma once
#endif

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class C_BreakableProp : public C_BaseAnimating
{
public:
	DECLARE_CLASS( C_BreakableProp, C_BaseAnimating );
	DECLARE_CLIENTCLASS();

	C_BreakableProp();

	virtual C_BasePlayer *GetPredictionOwner( void );
	virtual bool PredictionErrorShouldResetLatchedForAllPredictables( void ) { return false; }
	
	virtual void SetFadeMinMax( float fademin, float fademax );

	// Copy fade from another breakable prop
	void CopyFadeFrom( C_BreakableProp *pSource );
};

#endif // C_BREAKABLEPROP_H
