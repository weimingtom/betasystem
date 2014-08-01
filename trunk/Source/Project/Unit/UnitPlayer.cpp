#include "UnitPlayer.hpp"

#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Camera2D/Camera2D.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"


UnitPlayer::UnitPlayer()
 : mDashFrame(0)
 , mGravity(0.0f)
 , mDashLockFrame(0)
 , mDashIDCount(0)
 , mSpecialDashFrame(0)
 , mIsWalk( false )
{
	mHP = kDefaultHP;
	mHPMax = kDefaultHP;
	mImageSize = Vector2(48,69);
	mImageType = PrincessImageLoader::ImageType_DebugTop;
	mPos = Vector2(0.0f,0.0f);
}

void UnitPlayer::Update()
{
	UnitBase::Update();

	// ダッシュ.
	if( mDashFrame ){ mDashFrame--; }
	if( mSpecialDashFrame ){ mSpecialDashFrame--; }
	if( mDashLockFrame ){ mDashLockFrame--; }
	
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
	
	if( IsDash() ){
		SetFontSize(12);
	    DrawFormatString(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y  ),
	    	GetColor(0,255,0) , "attack" );
    }

	int hold_frame = KeyInput()->GetHoldFrame( InputKey::Type_J );
	if( hold_frame > 70 ){ hold_frame = 70; }
	DrawCircle(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
	    	hold_frame,
	    	(hold_frame == 70) ? GetColor(255,0,0) : GetColor(0,255,0),
			FALSE );
}

void UnitPlayer::BeginDash( Vector2 dash_vec )
{
	if( mDashLockFrame ){ return; }
	mDashLockFrame = 30;
	mSpeed = dash_vec * 18.0f;

	SingletonSoundLoader::Get()->Play( NameOf(SoundType_Dash) );
}

void UnitPlayer::BeginAttack( Vector2 dash_vec )
{
	mDashIDCount++;
	if( mDashIDCount > 10000 ){ mDashIDCount = 0; }

	mDashFrame = 25;
	mDashLockFrame = 35;
	mSpeed = dash_vec * 8.0f;

	SingletonSoundLoader::Get()->Play( NameOf(SoundType_Dash) );
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

bool UnitPlayer::IsSpecialDash() const{
	return ( mSpecialDashFrame != 0 );
}

bool UnitPlayer::IsJump() const{
	return ( mHeight != 0.0f );
}

void UnitPlayer::Walk( Vector2 add_pos ){
	mPos += add_pos;
	if( add_pos.x != 0.0f || add_pos.y != 0.0f ){
		mDir = add_pos.Normalize();
		mIsWalk = true;
	}else{
		mIsWalk = false;
	}
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

