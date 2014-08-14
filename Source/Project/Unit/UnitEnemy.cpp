#include "UnitEnemy.hpp"

#include <assert.h>
#include "Global.hpp"
#include "Project/Camera2D/Camera2D.hpp"
#include "Project/Shot/ShotBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"

//! 敵パラメータ.
struct EnemyStatus
{
	int mHP;		//!< ライフ.
	int mMoveSpeed;	//!< 移動速度.
	int mWeight;	//!< 重さ
};


EnemyStatus const sEnemyStatusList[] =
{
	// ライフ、速度、重さ
	{12,1,1,},
	{3,3,1,},
	{1,3,1,},
	{3,1,5,},
};

UnitEnemy::UnitEnemy() :
 mEnemyID(EnemyID_Normal),
 mState( State_Idle ),
 mFrame(0)
 , mIsFollowShot( false )
{
}

void UnitEnemy::Initialize( EnemyID enemy_id )
{
	assert( ARRAY_SIZE(sEnemyStatusList) == EnemyID_Num );
	assert( enemy_id < EnemyID_Num );

	mEnemyID = enemy_id;
	EnemyStatus const status = sEnemyStatusList[enemy_id];
	mMoveSpeed = status.mMoveSpeed;
	mHP = status.mHP;
	mHPMax = status.mHP;
	mWeight = status.mWeight;
	mExp = 30;

	mState=  State_Idle;
}

void UnitEnemy::Update()
{
	mIsAttack = (mState == State_ShotReady);
	mIsWalk = (mState == State_Chase);
	if( mIsAttack ){ mIsWalk = false; }

	assert( ( mIsAttack && mIsWalk ) == false );

	UnitBase::Update();

	if( mState != State_DeadRequest && mState != State_Dead ){
		if( mHP <= 0 ){
			SingletonSoundLoader::Get()->Play( NameOf(SoundType_Dead) );
			mState = State_DeadRequest;
			mFrame = 50;
		}
	}

	switch( mState )
	{
	case State_Idle:
		{
			Vector2 const to_vec = gUnitPlayer().GetPos() - mPos;
			if( to_vec.Length() < 150 ){
				mState = State_Exclamation;
				mFrame = 35;
			}
		}
		break;
	case State_Exclamation:
		mFrame -- ;
		if( mFrame == 0 ){
			mState = State_Chase;
		} 
		break;
	case State_Chase:
		{
			Vector2 move_vec = gUnitPlayer().GetPos() - mPos ;
			move_vec.Normalize();
			mPos += move_vec * this->mMoveSpeed;
			mDir = move_vec;
			
			//近付いたらショット.
			Vector2 move_vec2 = gUnitPlayer().GetPos() - mPos ;
			if( move_vec2.Length() < 150 ){
				mState = State_ShotReady;
				mFrame = 50;
				mIsFollowShot = false;
			}
		}
		break;
	case State_ShotReady:
		mFrame --;
		if( mFrame == 0 ){ mState = State_Shot; }
		break;
	case State_Shot:
		{
			Vector2 speed = gUnitPlayer().GetPos() - mPos;
			speed.Normalize();
			gShotManager().ShotRequest( mPos, speed, mIsFollowShot );
			mState = State_Chase;
		}
		break;
	case State_DeadRequest:
		{
			mFrame -- ;
			if( mFrame == 0 ){
				mState = State_Dead;
			}
		}
		break;
	case State_Dead:
		break;
	}
}

void UnitEnemy::Draw()
{
	if( mState == State_Dead ){ return; }

	// 攻撃準備
	if( mState == State_ShotReady ){
		SetFontSize(12);
	    DrawCircle(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
	    	mFrame ,
			mIsFollowShot ? GetColor(255,0,0) : GetColor(0,255,0) , 
	    	FALSE );
	    DrawCircle(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
	    	mFrame - 3,
			mIsFollowShot ? GetColor(255,0,0) : GetColor(0,255,0) , 
	    	FALSE );
	    DrawCircle(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
	    	mFrame - 6,
			mIsFollowShot ? GetColor(255,0,0) : GetColor(0,255,0) , 
	    	FALSE );
	}

	if( this->IsDamaged() ){
		if( mDamageFrame % 5 == 0 ){
			return;
		}
	}

	if( mState == State_DeadRequest ){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,mFrame*5);
	}

	DrawUnit( mIsWalk, mIsAttack );
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	SetFontSize(12);
	
/*
    DrawFormatString(
    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y +10),
    	GetColor(0,255,0) , "ID:%d", mEnemyID );
*/

	if( mState == State_Exclamation ){
		SetFontSize(64);
	    DrawFormatString(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y - 64),
	    	GetColor(0,255,0) , "！" );
	}

}

bool UnitEnemy::IsDead() const
{
	return ( mState == State_Dead || mState == State_DeadRequest );
}


UnitEnemy& gUnitEnemy( int index )
{
    static UnitEnemy sUnitEnemy[kEnemyMax];
    return sUnitEnemy[index];
}
