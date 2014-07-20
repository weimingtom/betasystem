#ifndef _StateActionGame_
#define _StateActionGame_

#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "DxLibWrapper/Random.hpp"
#include "DxLibWrapper/Color.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

extern bool gIsVisibleCollision;


//! ユニットの基底クラス.
class UnitBase
{
public:
	UnitBase()
	 : mHeight(0.0f)
	 , mSize( Vector2(48,48) )
	 , mHP(21)
	 , mIsDead(false)
	 , mDamageFrame(0)
	 , mImageType( ProjectImageLoader::ImageType_Enemy )
	 , mImageSize( Vector2(64,64) )
	{}
	virtual ~UnitBase(){}
public:
	virtual void Update()
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
	
	virtual void PreDraw()
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
	virtual void Draw()
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
		
		if( !gIsVisibleCollision ){
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
	float GetHeight() const {
		return mHeight;
	}
	//! 座標設定.
	void SetPos( Vector2 pos ){
		mPos = pos;
	}
	//! 座標取得.
	Vector2 GetPos() const {
		return mPos;
	}
	//! サイズ取得
	Vector2 GetSize() const{
		return mSize;
	}
	//! スピード設定.
	void SetSpeed( Vector2 speed ){
		mSpeed = speed;
	}
	
	void Damage( int damage ){
		mDamageFrame = 45;
		mHP -= damage;
	}
	
	bool IsDead() const{
		return mIsDead;
	}
	
	bool IsDamaged() const{
		return ( mDamageFrame != 0 );
	}
	
	int GetHP() const{ return mHP; }
	
protected:
	Vector2 mPos;
	Vector2 mSize;
	float mHeight;
	Vector2 mSpeed;
	int mHP;
	bool mIsDead;
	int mDamageFrame;
	ProjectImageLoader::ImageType mImageType;
	Vector2 mImageSize;
	Vector2 mDir;		//!< 向き.
};

//! プレイヤーユニット.
class UnitPlayer : public UnitBase
{
public:
	UnitPlayer()
	 : mDashFlag(false)
	 , mGravity(0.0f)
	{
		mImageSize = Vector2(64,90);
		mImageType = ProjectImageLoader::ImageType_DebugTop;
		mPos = Vector2(300.0f,300.0f);
	}
public:
	virtual void Update() override
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
	//! ダッシュする
	void BeginDash( Vector2 dash_vec ){
		mDashFlag = true;
		mSpeed = dash_vec * 18.0f;
		SingletonSoundLoader::Get()->Play( NameOf(SoundType_OK) );
	}
	//! ジャンプする
	void BeginJump(){
		if( mHeight <= 0.0f ){
			mGravity = 8.0f;
			SingletonSoundLoader::Get()->Play( NameOf(SoundType_Decide) );
		}
	}
	bool IsDash() const{
		return mDashFlag;
	}
	bool IsJump() const{
		return ( mHeight != 0.0f );
	}
	void AddPos( Vector2 add_pos ){
		mPos += add_pos;
		if( add_pos.x != 0.0f || add_pos.y != 0.0f ){
    		mDir = add_pos.Normalize();
    	}
	}
	Vector2 GetDir() const {
		return mDir;
	}
private:
	bool mDashFlag;
	float mGravity;		//!< 重力
};

extern UnitPlayer gUnitPlayer;


//! 敵ユニット.
class UnitEnemy : public UnitBase
{
public:
	UnitEnemy(){}
	~UnitEnemy(){}

public:
	virtual void Update() override
	{
		UnitBase::Update();

		//追尾
		Vector2 move_vec = gUnitPlayer.GetPos() - mPos ;
		move_vec.Normalize();
		mPos += move_vec / 2;
		
		mDir = move_vec;
	}
};

//! アクションゲームシーン.
class StateActionGame : public StateBase
{
public:
    StateActionGame();
    ~StateActionGame(){}
public:
	void Update();
	void Draw();
private:
	static int const kEnemyMax = 32;
private:
    UnitEnemy mEnemy[kEnemyMax];
    int mStageFrame;
};

#endif
