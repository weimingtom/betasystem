#include "UnitPlayer.hpp"

#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Camera2D/Camera2D.hpp"


UnitPlayer::UnitPlayer()
 : mDashFrame(0)
 , mGravity(0.0f)
 , mDashLockFrame(0)
 , mDashCount(0)
{
	mImageSize = Vector2(64,90);
	mImageType = PrincessImageLoader::ImageType_DebugTop;
	mPos = Vector2(0.0f,0.0f);
}

void UnitPlayer::Update()
{
	UnitBase::Update();

	// ダッシュ.
	if( mDashFrame ){ mDashFrame--; }
	if( mDashLockFrame ){ mDashLockFrame--; }
	
	// ジャンプ.
	mHeight += mGravity; // 重力.
	mGravity -= 0.5f;
	if( mHeight < 0.0f ){
		mHeight = 0.0f;
		mGravity = 0.0f;
	}
}

void UnitPlayer::Draw()
{
	UnitBase::Draw();
	
	if( IsDash() ){
		SetFontSize(12);
	    DrawFormatString(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
	    	GetColor(0,255,0) , "dash!" );
    }
}

void UnitPlayer::BeginDash( Vector2 dash_vec )
{
	if( mDashLockFrame ){ return; }
	mDashCount++;
	if( mDashCount > 10000 ){ mDashCount = 0; }
	mDashFrame = 25;
	mDashLockFrame = 40;
	mSpeed = dash_vec * 18.0f;
	SingletonSoundLoader::Get()->Play( NameOf(SoundType_OK) );
}

void UnitPlayer::BeginJump(){
	if( mDashLockFrame ){ return; }
	if( mHeight <= 0.0f ){
		mGravity = 8.0f;
		SingletonSoundLoader::Get()->Play( NameOf(SoundType_Decide) );
	}
}

bool UnitPlayer::IsDash() const{
	return (mDashFrame != 0);
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

