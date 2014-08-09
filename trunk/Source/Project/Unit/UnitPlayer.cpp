﻿#include "UnitPlayer.hpp"

#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Camera2D/Camera2D.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "UnitEnemy.hpp"

UnitPlayer::UnitPlayer()
 : mDashFrame(0)
 , mGravity(0.0f)
 , mDashLockFrame(0)
 , mSpecialDashFrame(0)
 , mAttackFrame(0)
 , mAttackLockFrame(0)
 , mAttackCanselCount(0)
 , mTargetEnemy(-1)
 , mIsTarget(false)
{
	mHP = kDefaultHP;
	mHPMax = kDefaultHP;
	mImageSize = Vector2(48,69);
	mImageType = PrincessImageLoader::ImageType_DebugTop;
	mPos = Vector2(0.0f,0.0f);
}

void UnitPlayer::Update()
{
	mIsWalk = mIsTarget;

	// ターゲットが居る
	if( mIsTarget ){

		//ターゲットが位置.
		if( mTargetEnemy == -1 ){
			Vector2 dir = mTargetPos - mPos;
			if( dir.Length() > 1.0f ){
				dir.Normalize();
				mDir = dir;
				mPos += dir*2;
			}else{
				mIsTarget = false;
			}
		}else{
		//ターゲットが敵.
			if( !gUnitEnemy(mTargetEnemy).IsDead() ){
				Vector2 dir = gUnitEnemy(mTargetEnemy).GetPos() - mPos;
				if( dir.Length() > 80.0f ){
					dir.Normalize();
					mDir = dir;
					mPos += dir*2;
				}else{
					dir.Normalize();
					BeginAttack(dir);
				}
			}else{
				mIsTarget = false;
			}
		}
	}

	UnitBase::Update();

	// ダッシュ.
	if( mDashFrame ){ mDashFrame--; }
	if( mSpecialDashFrame ){ mSpecialDashFrame--; }
	if( mDashLockFrame ){ mDashLockFrame--; }
	if( mAttackFrame ){ mAttackFrame--; }
	if( mAttackLockFrame ){ mAttackLockFrame--; }
	
	if( mAttackLockFrame == 0 ){ mAttackCanselCount = 0; }
	
	// ジャンプ.
	mHeight += mGravity; // 重力.
	
	if( mHeight != 0.0f ){
		mGravity -= 0.5f;
	}
	if( mHeight < 0.0f ){
		mHeight = 0.0f;
		mGravity = 0.0f;
		SingletonSoundLoader::Get()->Play( NameOf(SoundType_Landing) );
	}
}

void UnitPlayer::Draw()
{
	DrawUnit( mIsWalk );
	
	if( IsAttack() ){
		SetFontSize(12);
	    DrawFormatString(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y  ),
	    	GetColor(0,255,0) , "attack[%d]", mAttackCanselCount );
    }
    DrawFormatString(
    	static_cast<int>( mTargetPos.x + gCamera2D().GetDrawOffset().x - 6 ),
    	static_cast<int>( mTargetPos.y + gCamera2D().GetDrawOffset().y  ),
    	GetColor(255,255,0) , "▼");
}

void UnitPlayer::BeginDash( Vector2 dash_vec )
{
	if( mDashLockFrame ){ return; }

	mDashLockFrame = 30;
	mSpeed = dash_vec * 10.0f;
	
	mAttackLockFrame = 0;
	mAttackFrame = 0;
	
	SingletonSoundLoader::Get()->Play( NameOf(SoundType_Dash) );
}

void UnitPlayer::BeginAttack( Vector2 dash_vec )
{
	if( !CanAttack() ){ return; }

	mAttackCanselCount ++;
	mAttackFrame = 30;
	mAttackLockFrame = 35; 
	mSpeed = dash_vec * 10.0f;

	SingletonSoundLoader::Get()->Play( NameOf(SoundType_Dash) );
}

bool UnitPlayer::CanAttack() const
{
	//この間キャンセル可能.
	int const kCanselMin = 10;
	int const kCanselMax= 25;

	if(
		kCanselMin < mAttackLockFrame && mAttackLockFrame < kCanselMax
		&& mAttackCanselCount < 3
	){
		return true;
	}
	
	return ( mAttackLockFrame == 0 );
}

void UnitPlayer::BeginJump(){
	if( mDashLockFrame ){ return; }
	if( mHeight <= 0.0f ){
		mGravity = 8.0f;
		SingletonSoundLoader::Get()->Play( NameOf(SoundType_Jump) );
	}
}

bool UnitPlayer::IsDash() const{
	return ( mDashFrame != 0 );
}

bool UnitPlayer::IsJump() const{
	return ( mHeight != 0.0f );
}

void UnitPlayer::Walk( Vector2 add_pos ){
	mPos += add_pos;
}

Vector2 UnitPlayer::GetDir() const {
	return mDir;
}

void UnitPlayer::Revive()
{
	mHP = kDefaultHP;
	mIsDead = false;
}

void UnitPlayer::FreeLock()
{
	mDashLockFrame = 0;
	mDashFrame = 0;
}

static UnitPlayer sUnitPlayer;

UnitPlayer& gUnitPlayer()
{
	return sUnitPlayer;
}

