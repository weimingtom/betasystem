#include "DxLibWrapper.hpp"

#include <memory>
#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "System/StateManagerBase.hpp"
#include "Project/ProjectStateManager.hpp"

std::auto_ptr< StateManagerBase > g_state_manager;

int InitApplication()
{
    int const font_size = 12;
    
    SetGraphMode( 640 , 480 , 16 ) ;
    ChangeWindowMode( TRUE ) ;
    if( DxLib_Init() == ApplicationFailure ) { return ApplicationFailure; }
    
    SetDrawScreen( DX_SCREEN_BACK );
    SetFontSize( font_size );
    
    g_state_manager.reset( new_ProjectStateManager() );
    g_state_manager->ChangeState( ProjectState_WorldMap );
    
    return ApplicationSuccess;
}

void LoopApplication()
{
    while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
    {
        g_state_manager->Update();
        
        ClearDrawScreen() ;    // 画面を初期化する
        g_state_manager->Draw();
        ScreenFlip() ;    // 裏画面の内容を表画面に反映させる
    }
}

int EndApplication()
{
    g_state_manager.reset(0);
    DxLib_End();
    return ApplicationSuccess;
}

