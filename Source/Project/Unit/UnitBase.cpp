#include "UnitBase.hpp"

#include "DxLibWrapper/Color.hpp"
#include "Project/Unit/Global.hpp"
#include "Project/Camera2D/Camera2D.hpp"

UnitBase::UnitBase()
 : mHeight(0.0f)
 , mSize( Vector2(64,64) )
 , mHP(3)
 , mHPMax(3)
 , mIsDead(false)
 , mDamageFrame(0)
 , mImageType( PrincessImageLoader::ImageType_Enemy )
 , mImageSize( Vector2(64,64) )
 , mWeight(1)
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
	DrawGraphInCamera(
		static_cast<int>( GetPos().x -32 ),
		static_cast<int>( GetPos().y -16 ),
		PrincessImageLoader::ImageType_Shadow,
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
	
	DrawUnit();
}

void UnitBase::DrawUnit()
{
    DrawGraphInCamera( 
    	static_cast<int>( GetPos().x - mImageSize.x / 2 ),
    	static_cast<int>( GetPos().y - GetHeight() - mImageSize.y ),
		mImageType,
		TRUE,
		( mDir.x < 0.0f ));

	//HP
    DrawBox(
    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x - 25),
    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x + 25 ),
    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y + 4 ),
    	GetColor(255,0,0) , TRUE);
    DrawBox(
    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x - 25),
    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x - 25 + (50 * mHP / mHPMax) ),
    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y + 4 ),
    	GetColor(0,255,0) , TRUE);

	if( IsVisibleCollision() ){
		// コリジョン
		DrawBox(
			static_cast<int>( GetPos().x - GetSize().x / 2 + gCamera2D().GetDrawOffset().x ),
			static_cast<int>( GetPos().y - GetSize().y / 2 + gCamera2D().GetDrawOffset().y ),
			static_cast<int>( GetPos().x + GetSize().x / 2 + gCamera2D().GetDrawOffset().x ),
			static_cast<int>( GetPos().y + GetSize().y / 2 + gCamera2D().GetDrawOffset().y ),
			ColorOf(255,0,0),
			FALSE
		);
	}
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
	mSpeed = speed * 10 / mWeight;
}

void UnitBase::Damage( int damage ){
	mDamageFrame = 55;
	mHP -= damage;
	if( mHP < 0 ){ mHP = 0; }
}

bool UnitBase::IsDead() const{
	return mIsDead;
}

bool UnitBase::IsDamaged() const{
	return ( mDamageFrame != 0 );
}

int UnitBase::GetHP() const{ return mHP; }


