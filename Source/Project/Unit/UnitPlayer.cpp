#include "UnitPlayer.hpp"

#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Camera2D/Camera2D.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "UnitEnemy.hpp"
#include "Global.hpp"

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
	mIsAttack = false;
	mIsWalk = mIsTarget;

	// 位置がターゲット.
	if( mIsTarget && !IsTargetEnemy() )
	{
		Vector2 dir = mTargetPos - mPos;
		if( dir.Length() > 1.0f ){
			dir.Normalize();
			AddPos( dir * 2 );
		}else{
			mIsTarget = false;
		}
	}
	
	// 敵がターゲット.
	if( mIsTarget && IsTargetEnemy() )
	{
		if( !gUnitEnemy(mTargetEnemy).IsDead() ){
			Vector2 dir = gUnitEnemy(mTargetEnemy).GetPos() - mPos;
			if( dir.Length() > 80.0f ){
				dir.Normalize();
				AddPos( dir * 2 );
			}else{
				mAttackFrame++;
				mIsAttack = true;
				mIsWalk = false;
				if( mAttackFrame > 30 ){
					gUnitEnemy(mTargetEnemy).Damage(1);
					mAttackFrame = 0;
					SingletonSoundLoader::Get()->Play( NameOf(SoundType_Hit) );
				}
			}
		}else{
			mIsTarget = false;
		}
	}

	UnitBase::Update();
}

void UnitPlayer::Draw()
{
	if( IsDamaged() ){
		if( mDamageFrame % 5 == 0 ){
			return;
		}
	}

	DrawUnit( mIsWalk, mIsAttack );
	
	SetFontSize(12);

    if( !mIsTarget ){ return; }
    if( IsTargetEnemy() ){
	    DrawFormatString(
	    	static_cast<int>( gUnitEnemy(mTargetEnemy).GetPos().x + gCamera2D().GetDrawOffset().x - 6 ),
	    	static_cast<int>( gUnitEnemy(mTargetEnemy).GetPos().y + gCamera2D().GetDrawOffset().y - 48 ),
	    	GetColor(255,255,0) , "▼");
    }else{
	    DrawFormatString(
	    	static_cast<int>( mTargetPos.x + gCamera2D().GetDrawOffset().x - 6 ),
	    	static_cast<int>( mTargetPos.y + gCamera2D().GetDrawOffset().y  ),
	    	GetColor(255,255,0) , "▼");
	}
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

void UnitPlayer::AddPos( Vector2 add_pos ){
	Vector2 next_pos = mPos + add_pos;
	if( GetMapChip( next_pos.x / 48, next_pos.y / 48 ) == 0 ){
		return;
	}

	mPos += add_pos;
	mDir = add_pos.Normalize();
}

Vector2 UnitPlayer::GetDir() const {
	return mDir;
}

void UnitPlayer::Revive()
{
	mHP = kDefaultHP;
	mIsDead = false;
	mPos = Vector2(500,500);
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

