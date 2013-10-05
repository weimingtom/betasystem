#ifndef include_e7906b92_f887_4c5d_8bba_b487c6df83e1
#define include_e7906b92_f887_4c5d_8bba_b487c6df83e1

#include "System/AnimFormat.hpp"

/**
	アニメーションの種類.
*/
enum AnimType
{
	AnimType_PlayerIdling,
	AnimType_PlayerCharge,
	AnimType_PlayerDeath,
	AnimType_PlayerGrave,
	AnimType_PlayerDash,
	AnimType_EnemyIdling,
	
	AnimType_Num,
};

/**
	アニメーションデータの取得.
*/
AnimFormat const& AnimDataOf( AnimType anim_type );

#endif // include_e7906b92_f887_4c5d_8bba_b487c6df83e1

