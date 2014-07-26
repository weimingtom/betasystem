﻿#include "UnitEnemy.hpp"

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
	{5,1,1,},
	{3,3,1,},
	{1,3,1,},
	{3,1,5,},
};

UnitEnemy::UnitEnemy() :
 mEnemyID(EnemyID_Normal),
 mDamagedID(-1),
 mState( State_Idle ),
 mFrame(0)
{}

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

	mState=  State_Idle;
}

void UnitEnemy::Update()
{
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
			
			//たまにショット.
			if( GetRand(100) == 0 ){
				mState = State_ShotReady;
				mFrame = 55;
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
			gShotManager().ShotRequest( mPos, speed );
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

	if( this->IsDamaged() ){
		if( mDamageFrame % 5 == 0 ){
			return;
		}
	}

	if( mState == State_DeadRequest ){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,mFrame*5);
	}

	DrawUnit();
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	SetFontSize(12);
	
    DrawFormatString(
    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
    	GetColor(0,255,0) , "ID:%d", mEnemyID );

	if( mState == State_Exclamation ){
		SetFontSize(64);
	    DrawFormatString(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y - 64),
	    	GetColor(0,255,0) , "！" );
	}

	if( mState == State_ShotReady ){
		SetFontSize(12);
	    DrawCircle(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
	    	mFrame ,
	    	GetColor(0,255,0) , 
	    	FALSE );
	}
}

bool UnitEnemy::IsDead() const
{
	return ( mState == State_Dead || mState == State_DeadRequest );
}