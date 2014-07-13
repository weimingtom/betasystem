#ifndef _StateActionGame_
#define _StateActionGame_

#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "DxLibWrapper/Random.hpp"


//! プレイヤー.
class PlayerStatus
{
public:
	PlayerStatus()
	 : mDashFlag(false)
	 , mHeight(0.0f)
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
	}
	//! ジャンプする
	void BeginJump(){
		if( mHeight <= 0.0f ){
			mGravity = 8.0f;
		}
	}
	//! ジャンプ高さ
	float GetHeight() const {
		return mHeight;
	}
	void AddPos( Vector2 add_pos ){
		mPos+= add_pos;
		if( add_pos.x != 0.0f || add_pos.y != 0.0f ){
    		mDir = add_pos;
    	}
	}
	Vector2 GetPos() const { return mPos; }
	Vector2 GetDir() const { return mDir; }
private:
	Vector2 mPos;
	bool mDashFlag;
	Vector2 mDashVec;
	Vector2 mDir;		//!< 向き.
	float mHeight;
	float mGravity;		//!< 重力
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

private:
    PlayerStatus mPlayer;
};

#endif
