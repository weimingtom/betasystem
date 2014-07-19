#ifndef _StateActionGame_
#define _StateActionGame_

#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "DxLibWrapper/Random.hpp"
#include "DxLibWrapper/Color.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

//! ユニットの基底クラス.
class UnitBase
{
public:
	UnitBase()
	 : mHeight(0.0f)
	 , mSize( Vector2(24,24) )
	{}
	virtual ~UnitBase(){}
public:
	//! 描画.
	virtual void Draw(){
		
		Vector2 kImageSize(64,64);
	    // 影
		DrawOval(
			static_cast<int>( GetPos().x ),
			static_cast<int>( GetPos().y ),
			static_cast<int>( (100 - GetHeight()) / 5 ),
			static_cast<int>( (100 - GetHeight()) / 12 ),
			ColorOf(155,155,155),
			TRUE );

		// キャラ
	    DrawGraph( 
	    	static_cast<int>( GetPos().x - kImageSize.x / 2 ),
	    	static_cast<int>( GetPos().y - GetHeight() - kImageSize.y ),
			ProjectImageLoader::ImageHandleOf( ProjectImageLoader::ImageType_Enemy ), TRUE );
		
		// コリジョン
		DrawBox(
			static_cast<int>( GetPos().x - GetSize().x / 2 ),
			static_cast<int>( GetPos().y - GetSize().y ),
			static_cast<int>( GetPos().x + GetSize().x / 2 ),
			static_cast<int>( GetPos().y  ),
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

protected:
	Vector2 mPos;
	Vector2 mSize;
	float mHeight;
};

//! プレイヤーユニット.
class UnitPlayer : public UnitBase
{
public:
	UnitPlayer()
	 : mDashFlag(false)
	 , mGravity(0.0f)
	{
		mPos = Vector2(300.0f,300.0f);
	}
public:
	void Update()
	{
		// ダッシュ
		if( mDashFlag ){
    		mPos += mDashVec;
    		mDashVec *= 0.8f;
    		if( fabs(mDashVec.x) < 0.01f && fabs(mDashVec.y) < 0.01f ){
    			mDashFlag = false;
    		}
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
		mDashVec = dash_vec * 18.0f;
		SingletonSoundLoader::Get()->Play( NameOf(SoundType_OK) );
	}
	//! ジャンプする
	void BeginJump(){
		if( mHeight <= 0.0f ){
			mGravity = 8.0f;
			SingletonSoundLoader::Get()->Play( NameOf(SoundType_Decide) );
		}
	}
	void AddPos( Vector2 add_pos ){
		mPos+= add_pos;
		if( add_pos.x != 0.0f || add_pos.y != 0.0f ){
    		mDir = add_pos.Normalize();
    	}
	}
	Vector2 GetDir() const {
		return mDir;
	}
private:
	bool mDashFlag;
	Vector2 mDashVec;
	Vector2 mDir;		//!< 向き.
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
	void Update()
	{
		// 追尾
		/*
		Vector2 move_vec = gUnitPlayer.GetPos() - mPos ;
		move_vec.Normalize();
		mPos += move_vec;
		*/
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
};

#endif
