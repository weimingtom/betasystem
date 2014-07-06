#include "StateCharacterGenerate.hpp"

#include <assert.h>
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"

StateCharacterGenerate::StateCharacterGenerate()
 : mGenerateNum(0)
{
}

void StateCharacterGenerate::Update()
{
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "キャラ生成テスト:Enterで再生成");
    
    char const* status_name[] =
    {
    	"HP ",
    	"ATK",
    	"DEF",
    	"SPD",
    	"TEC",
    	"LUK",
    };
    
    assert( StatusType_Num == ARRAY_SIZE(status_name) );

    DrawFormatString( 0, 20 , ColorOf(255,255,255), "id:%03d", mUnitStatus.mID );

	int const kBaseY = 40;
    for( int i = 0 ; i < StatusType_Num ; i++ ){
        for( int j = 0 ; j < mUnitStatus.mStatus[i] ; j++ ){
			int color = ColorOf(255,255,255);
			if( mUnitStatus.mStatus[i] >= 15 ){
				color = ColorOf(250,0,0);
			}else if( mUnitStatus.mStatus[i] >= 12 ){
				color = ColorOf(250,250,0);
			}else if( mUnitStatus.mStatus[i] <= 7 ){
				color = ColorOf(0,0,250);
			}
	        DrawFormatString( 50 + j * 12 , kBaseY + i*10 , color ,"■" );
        }
        DrawFormatString( 0, kBaseY + i*10, ColorOf(255,255,255), "%s:%03d", status_name[i], mUnitStatus.mStatus[i] );
    }
    
    if( KeyInput()->IsTrig( InputKey::Type_Enter ) ){
    	mUnitStatus.SetRandom(mGenerateNum);
    	mGenerateNum++;
    }
}

void StateCharacterGenerate::Draw()
{
}

