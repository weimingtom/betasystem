#ifndef ShotBase_hpp_
#define ShotBase_hpp_

#include "System/Vector2.hpp"
#include "Project/Camera2D/Camera2D.hpp"
#include "Project/Unit/Global.hpp"
#include "Project/Unit/UnitPlayer.hpp"

// ショット
class ShotBase
{
public:
	ShotBase()
		: mState( State_None )
		, mLifeFrame(0)
		, mSize( Vector2(32,32) )
		, mIsFollow(false)
	{
	}
public:
	/**
		更新.
	*/
	void Update()
	{
		// 追尾弾
		if( mIsFollow ){
			Vector2 target_dir = gUnitPlayer().GetPos() - mPos ;
			target_dir.Normalize();
			Vector2 last_dir = mDir * 10 + target_dir;
			mDir = last_dir.Normalize();
		}

		mPos += mDir * mSpeed;

		if( mLifeFrame ){ mLifeFrame--; }
		if( mLifeFrame == 0 ){
			mState = State_None;
			mPos = Vector2(0.0f,0.0f);
			mDir = Vector2(0.0f,0.0f);
			mSpeed = 0.0f;
		}
	}
	/**
		描画.
	*/
	void Draw()
	{
		if( !IsLife() ){ return; }

	    DrawCircle(
	    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y ),
	    	static_cast<int>( 8 ),
	    	mIsFollow ? GetColor(255,0,0) : GetColor(0,255,0) , TRUE
		);

		if( IsVisibleCollision() ){
		    DrawBox(
		    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x - mSize.x ),
		    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y - mSize.y ),
		    	static_cast<int>( mPos.x + gCamera2D().GetDrawOffset().x + mSize.x ),
		    	static_cast<int>( mPos.y + gCamera2D().GetDrawOffset().y + mSize.y ),
		    	GetColor(0,255,0) , FALSE
			);
		}
	}
	/**
		初期化.
	*/
	void Initialize( Vector2 pos, Vector2 dir )
	{
		mPos = pos;
		mDir = dir;
		mSpeed = 6.0f;
		mLifeFrame = 100;
		mState = State_Shot;
		
		mIsFollow = (GetRand(1) == 0);
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
	/**
		サイズ取得.
	*/
	Vector2 GetSize() const { return mSize; }
private:
	enum State{
		State_None,
		State_Shot,
	};
private:
	Vector2 mPos;
	Vector2 mSize;
	Vector2 mDir;
	float mSpeed;
	State mState;
	int mLifeFrame;
	bool mIsFollow;
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

	ShotBase const& GetShot(int index){
		return mShotList[index];
	}
public:
	static int const kShotNum = 32;
private:
	ShotBase mShotList[kShotNum];
};

/**
	ショットマネージャの取得.
*/
ShotManager& gShotManager();

#endif // ShotBase_hpp_

