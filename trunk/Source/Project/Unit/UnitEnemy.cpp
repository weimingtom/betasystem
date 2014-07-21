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
	{3,2,1,},
	{2,4,1,},
	{1,6,1,},
	{3,1,5,},
};

void UnitEnemy::Initialize( EnemyID enemy_id )
{
	mEnemyID = enemy_id;
	assert( ARRAY_SIZE(sEnemyStatusList) == EnemyID_Num );
	assert( mEnemyID < EnemyID_Num );
	EnemyStatus const status = sEnemyStatusList[enemy_id];
	
	this->mMoveSpeed = status.mMoveSpeed;
	this->mHP = status.mHP;
	this->mWeight = status.mWeight;
	this->mIsDead = false;
}

void UnitEnemy::Update()
{
	UnitBase::Update();

	//追尾
	Vector2 move_vec = gUnitPlayer().GetPos() - mPos ;
	move_vec.Normalize();
	mPos += move_vec * this->mMoveSpeed;
	
	mDir = move_vec;
}

void UnitEnemy::Draw()
{
	UnitBase::Draw();
	
	if( IsDead() ){ return; }
	
    DrawFormatString(
    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
    	GetColor(0,255,0) , "%d", mEnemyID );
}
