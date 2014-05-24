#include "StateDebugTop.hpp"

#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/Range.hpp"

namespace Princess{

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
    mIndex = Clamp( 0, mIndex, ProjectStateManager::State_Num - 1 );
    
    if( KeyInput()->IsTrig( InputKey::Type_Enter ) ) 
    {
        ProjectStateManager::GetInstance()->ChangeState( ProjectStateManager::new_State( static_cast<ProjectStateManager::State>(mIndex) ) );
    }
}

void StateDebugTop::Draw()
{
    int const kMarginY = 15;
    DrawFormatString( 0 , mIndex*kMarginY, ColorOf(0,255,0) , "→");
    
    for( int i = 0 ; i < ProjectStateManager::State_Num ; i++ )
    {
        DrawFormatString( 20 , i*kMarginY, ColorOf(0,255,0) , ProjectStateManager::NameOf( static_cast<ProjectStateManager::State>(i) ).c_str() );
    }
}

} // namespace Princess
