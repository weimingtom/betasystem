#ifndef ShotBase_hpp_
#define ShotBase_hpp_

#include "System/Vector2.hpp"
#include "Project/Camera2D/Camera2D.hpp"

// ショット
class ShotBase
{
public:
	ShotBase()
		: mState( State_None )
		, mLifeFrame(0)
		, mSize( Vector2(6,6) )
	{
	}
public:
	/**
		更新.
	*/
	void Update()
	{
		mPos += mSpeed;
		if( mLifeFrame ){ mLifeFrame--; }
		if( mLifeFrame == 0 ){
			mState = State_None;
			mPos = Vector2(0.0f,0.0f);
			mSpeed = Vector2(0.0f,0.0f);
		}
	}
	/**
		描画.
	*/
	void Draw()
	{
		if( !IsLife() ){ return; }
	    DrawOval(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
	    	static_cast<int>( mSize.x ),
	    	static_cast<int>( mSize.y ),
	    	GetColor(0,255,0) , TRUE
		);
	}
	/**
		初期化.
	*/
	void Initialize( Vector2 pos, Vector2 speed )
	{
		mPos = pos;
		mSpeed = speed * 4;
		mLifeFrame = 300;
		mState = State_Shot;
	}
	/**
		外部から消す.
	*/
	void Destroy()
	{
		mState = State_None;
	}
	/**
		ショットとして使えるか。
	*/
	bool IsLife() const { return ( mState != State_None ); }
	/**
		座標取得.
	*/
	Vector2 GetPos() const { return mPos; }
private:
	enum State{
		State_None,
		State_Shot,
	};
private:
	Vector2 mPos;
	Vector2 mSize;
	Vector2 mSpeed;
	State mState;
	int mLifeFrame;
};

// ショット管理.
class ShotManager
{
public:
	/**
		更新処理.
	*/
	void Update()
	{
		for( int i = 0 ; i < kShotNum ; i++ ){
			mShotList[i].Update();
		}
	}
	/**
		描画処理.
	*/
	void Draw()
	{
		SetFontSize(12);
		for( int i = 0 ; i < kShotNum ; i++ ){
			mShotList[i].Draw();
/*
		    DrawFormatString(
		    	0 , 150 + i * 10,
		    	GetColor(0,255,0) ,
		    	"ID:%d,[%f,%f]",
		    	i,
		    	mShotList[i].GetPos().x,
		    	mShotList[i].GetPos().y );
*/
		}
	}
	/**
		ショットリクエスト.
	*/
	void ShotRequest( Vector2 pos, Vector2 speed )
	{
		for( int i = 0 ; i < kShotNum ; i++ ){
			if( !mShotList[i].IsLife() ){
				mShotList[i].Initialize( pos, speed );
				return;
			}
		}
	}

private:
	static int const kShotNum = 32;
private:
	ShotBase mShotList[kShotNum];
};

/**
	ショットマネージャの取得.
*/
ShotManager& gShotManager();

#endif // ShotBase_hpp_

