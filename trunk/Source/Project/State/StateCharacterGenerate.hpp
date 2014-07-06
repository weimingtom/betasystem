#ifndef _StateCharacterGenerate_
#define _StateCharacterGenerate_

#include "System/StateBase.hpp"
#include "DxLibWrapper/Random.hpp"

/**
*/
class StateCharacterGenerate : public StateBase
{
public:
    StateCharacterGenerate();
    ~StateCharacterGenerate(){}
public:
	void Update();
	void Draw();

private:
	//! ステータス種別.
    enum StatusType{
        StatusType_HP,
        StatusType_Power,
        StatusType_Deffence,
        StatusType_Speed,
        StatusType_Technique,
        StatusType_Luck,
        StatusType_Num,
    };
private:
    //! ユニットのステータス
    class UnitStatus
    {
    public:
        //! コンストラクタ
        UnitStatus()
        {
			for( int i = 0 ; i < StatusType_Num ; i++ ){
				mStatus[i] = 0;
			}
			mID = 0;
        }
    public:
        //! ランダムでステータスを決定する.
        void SetRandom( int id )
        {
        	for( int i = 0 ; i < StatusType_Num ; i++ ){
        		mStatus[i] = GetRand(5,15);
        	}
        	mID = id;
        }
    public:
    	int mStatus[StatusType_Num];
    	int mID;
    };
private:
    UnitStatus mUnitStatus;
    int mGenerateNum;
};

#endif
