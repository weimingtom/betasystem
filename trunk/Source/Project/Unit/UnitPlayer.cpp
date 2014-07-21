#include "UnitPlayer.hpp"

#include "Project/Singleton/SingletonSoundLoader.hpp"


UnitPlayer::UnitPlayer()
 : mDashFlag(false)
 , mGravity(0.0f)
{
	mImageSize = Vector2(64,90);
	mImageType = ProjectImageLoader::ImageType_DebugTop;
	mPos = Vector2(0.0f,0.0f);
}

void UnitPlayer::Update()
{
	// ダッシュ
	UnitBase::Update();

	if( fabs(mSpeed.x) < 0.5f && fabs(mSpeed.y) < 0.5f ){
		mDashFlag = false;
	}
	
	// ジャンプ.
	mHeight += mGravity; // 重力.
	mGravity -= 0.5f;
	if( mHeight < 0.0f ){
		mHeight = 0.0f;
		mGravity = 0.0f;
	}
}

void UnitPlayer::BeginDash( Vector2 dash_vec ){
	mDashFlag = true;
	mSpeed = dash_vec * 18.0f;
	SingletonSoundLoader::Get()->Play( NameOf(SoundType_OK) );
}

void UnitPlayer::BeginJump(){
	if( mHeight <= 0.0f ){
		mGravity = 8.0f;
		SingletonSoundLoader::Get()->Play( NameOf(SoundType_Decide) );
	}
}

bool UnitPlayer::IsDash() const{
	return mDashFlag;
}

bool UnitPlayer::IsJump() const{
	return ( mHeight != 0.0f );
}

void UnitPlayer::AddPos( Vector2 add_pos ){
	mPos += add_pos;
	if( add_pos.x != 0.0f || add_pos.y != 0.0f ){
		mDir = add_pos.Normalize();
	}
}

Vector2 UnitPlayer::GetDir() const {
	return mDir;
}

void UnitPlayer::Revive()
{
	mHP = 3;
	mIsDead = false;
}


static UnitPlayer sUnitPlayer;

UnitPlayer& gUnitPlayer()
{
	return sUnitPlayer;
}

