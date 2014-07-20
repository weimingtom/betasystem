#include "UnitBase.hpp"

#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "DxLibWrapper/Color.hpp"
#include "Project/Unit/Global.hpp"

UnitBase::UnitBase()
 : mHeight(0.0f)
 , mSize( Vector2(48,48) )
 , mHP(21)
 , mIsDead(false)
 , mDamageFrame(0)
 , mImageType( ProjectImageLoader::ImageType_Enemy )
 , mImageSize( Vector2(64,64) )
{
}

void UnitBase::Update()
{
		mPos += mSpeed;
	mSpeed *= 0.8f;
	
	if( mDamageFrame ){
		mDamageFrame--;
	}

	if( !IsDamaged() ){
		if( mHP <= 0 ){
			mIsDead = true;
		}
	}
}

void UnitBase::PreDraw()
{
	if( this->IsDead() ){
		return;
	}
	
	if( this->IsDamaged() ){
		if( mDamageFrame % 5 == 0 ){
			return;
		}
	}
    // 影
	DrawOval(
		static_cast<int>( GetPos().x ),
		static_cast<int>( GetPos().y ),
		static_cast<int>( (100 - GetHeight()) / 5 ),
		static_cast<int>( (100 - GetHeight()) / 12 ),
		ColorOf(155,155,155),
		TRUE );
}

//! 描画.
void UnitBase::Draw()
{
	if( this->IsDead() ){
		return;
	}
	
	if( this->IsDamaged() ){
		if( mDamageFrame % 5 == 0 ){
			return;
		}
	}
	
	// キャラ
	if( mDir.x < 0.0f ){
	    DrawGraph( 
	    	static_cast<int>( GetPos().x - mImageSize.x / 2 ),
	    	static_cast<int>( GetPos().y - GetHeight() - mImageSize.y ),
			ProjectImageLoader::ImageHandleOf(mImageType), TRUE );
	}else{
	    DrawTurnGraph( 
	    	static_cast<int>( GetPos().x - mImageSize.x / 2 ),
	    	static_cast<int>( GetPos().y - GetHeight() - mImageSize.y ),
			ProjectImageLoader::ImageHandleOf(mImageType), TRUE );
	}
	
	if( !IsVisibleCollision() ){
		return;
	}
	// コリジョン
	DrawBox(
		static_cast<int>( GetPos().x - GetSize().x / 2 ),
		static_cast<int>( GetPos().y - GetSize().y / 2 ),
		static_cast<int>( GetPos().x + GetSize().x / 2 ),
		static_cast<int>( GetPos().y + GetSize().y / 2 ),
		ColorOf(255,0,0),
		FALSE
	);
}

//! ジャンプ高さ
float UnitBase::GetHeight() const {
	return mHeight;
}
//! 座標設定.
void UnitBase::SetPos( Vector2 pos ){
	mPos = pos;
}
//! 座標取得.
Vector2 UnitBase::GetPos() const {
	return mPos;
}
//! サイズ取得
Vector2 UnitBase::GetSize() const{
	return mSize;
}
//! スピード設定.
void UnitBase::SetSpeed( Vector2 speed ){
	mSpeed = speed;
}

void UnitBase::Damage( int damage ){
	mDamageFrame = 45;
	mHP -= damage;
}

bool UnitBase::IsDead() const{
	return mIsDead;
}

bool UnitBase::IsDamaged() const{
	return ( mDamageFrame != 0 );
}

int UnitBase::GetHP() const{ return mHP; }


