#ifndef _StateActionGame_
#define _StateActionGame_

#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "DxLibWrapper/Random.hpp"

class StateActionGame : public StateBase
{
public:
    StateActionGame();
    ~StateActionGame(){}
public:
	void Update();
	void Draw();

private:
    class PlayerStatus
    {
    public:
    	PlayerStatus()
    	 : mDashFlag(false)
    	{
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
    		
    		// アタック
    		if( mAttackFlag ){
    			mAttackFrame--;
    			if( mAttackFrame <= 0 ){
    				mAttackFlag = false;
    			}
    		}
    	}
    	void BeginDash( Vector2 dash_vec ){
    		mDashFlag = true;
    		mDashVec = dash_vec * 12.0f;
    	}
    	void BeginAttack(){
    		mAttackFlag = true;
    		mAttackFrame = 10;
    	}
		bool IsAttack() const {
			return mAttackFlag;
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
    	bool mAttackFlag;
    	int mAttackFrame;
    	Vector2 mDir; //!< 向き.
    };
private:
    PlayerStatus mPlayerStatus;
};

#endif
