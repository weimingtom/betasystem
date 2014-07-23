#include "UnitEnemy.hpp"

#include <assert.h>
#include "Global.hpp"
#include "Project/Camera2D/Camera2D.hpp"
#include "System/ArraySize.hpp"

//! 敵パラメータ.
struct EnemyStatus
{
	int mHP;		//!< ライフ.
	int mMoveSpeed;	//!< 移動速度.
	int mWeight;	//!< 重さ
};


EnemyStatus const sEnemyStatusList[] =
{
	{3,1,1,},
	{1,3,1,},
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
	
	this->mMoveSpeed = status.mMoveSpeed;
	this->mHP = status.mHP;
	this->mHPMax = status.mHP;
	this->mWeight = status.mWeight;
	this->mIsDead = false;
}

void UnitEnemy::Update()
{
	UnitBase::Update();


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
		}
		break;
	}
}

void UnitEnemy::Draw()
{
	UnitBase::Draw();
	
	if( IsDead() ){ return; }
	
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

}
