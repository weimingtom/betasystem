#include "StateDebugTop.hpp"

#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/Range.hpp"

StateDebugTop::StateDebugTop()
 : mIndex(0)
{
}

void StateDebugTop::Update()
{
    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){
        --mIndex;
    }
    else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){
        ++mIndex;
    }
    mIndex = Clamp( 0, mIndex, SingletonProjectStateManager::State_Num );
}

void StateDebugTop::Draw() const
{
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "デバッグトップ");
    DrawFormatString( 0 , mIndex*10 , ColorOf(0,255,0) , "→");
}

