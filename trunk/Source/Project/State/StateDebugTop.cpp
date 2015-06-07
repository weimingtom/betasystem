#include "StateDebugTop.hpp"

#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/SingletonStateManager.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/Range.hpp"

namespace Princess{

StateDebugTop::StateDebugTop()
 : mIndex(0)
{
}

void StateDebugTop::Update()
{
    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){ mIndex--; }
    else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){ mIndex++; }

    mIndex = Clamp( 0, mIndex, StateManager::State_Num - 1 );
    
    if( KeyInput()->IsTrig( InputKey::Type_Enter ) ) {
        StateManager::GetInstance()->ChangeState( StateManager::new_State( static_cast<StateManager::State>(mIndex) ) );
    }
}

void StateDebugTop::Draw()
{
    int const kFontSize = 12;
    SetFontSize(kFontSize);
    DrawFormatString( 0 , 0, ColorOf(0,255,0) , "[%s]", __FUNCTION__ );
    DrawFormatString( 0 , kFontSize, ColorOf(0,255,0) , "ステート選択デバッグ画面です.遷移したいステートを選択できます.F1キーでこの画面に戻ります." );

    int const kBaseY = 40;
    int const kMarginY = 15;
    DrawFormatString( 0 , kBaseY + mIndex*kMarginY, ColorOf(0,255,0) , "→");
    for( int i = 0 ; i < StateManager::State_Num ; i++ )
    {
        DrawFormatString( 20 , kBaseY + i*kMarginY, ColorOf(0,255,0) , "%d.%s",i,StateManager::NameOf( static_cast<StateManager::State>(i) ).c_str() );
    }
    
    DrawGraph(300,200, PrincessImageLoader::ImageHandleOf( PrincessImageLoader::ImageType_DebugTop ) , FALSE );
}

} // namespace Princess
