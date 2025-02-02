//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#include "cbase.h"
#include "tf_weapon_bonesaw.h"

#ifdef CLIENT_DLL
#include "tf_weapon_medigun.h"
#include "c_tf_player.h"
#include "tf_viewmodel.h"
#endif

//=============================================================================
//
// Weapon Bonesaw tables.
//

IMPLEMENT_NETWORKCLASS_ALIASED( TFBonesaw, DT_TFWeaponBonesaw )

BEGIN_NETWORK_TABLE( CTFBonesaw, DT_TFWeaponBonesaw )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CTFBonesaw )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( tf_weapon_bonesaw, CTFBonesaw );
PRECACHE_WEAPON_REGISTER( tf_weapon_bonesaw );

#ifdef CLIENT_DLL
void CTFBonesaw::OnDataChanged( DataUpdateType_t updateType )
{
	BaseClass::OnDataChanged( updateType );
	UpdateChargePoseParam();
}

bool CTFBonesaw::Deploy( void )
{
	if ( BaseClass::Deploy() )
	{
		UpdateChargePoseParam();
		return true;
	}

	return false;
}

void CTFBonesaw::UpdateChargePoseParam( void )
{
	CTFPlayer *pOwner = GetTFPlayerOwner();
	if ( !pOwner )
		return;

	CWeaponMedigun *pMedigun = pOwner->GetMedigun();
	if ( pMedigun )
	{
		SetPoseParameter( "syringe_charge_level", pMedigun->GetChargeLevel() );

		CBaseViewModel *vm = pOwner->GetViewModel( m_nViewModelIndex );
		if ( vm )
			vm->SetPoseParameter( "syringe_charge_level", pMedigun->GetChargeLevel() );
	}
}

#endif
