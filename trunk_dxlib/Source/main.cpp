#include <DxLib.h>
#include "DxLibWrapper/ReturnVariable.hpp"
#include <memory>
#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "System/StateManagerBase.hpp"
#include "Project/ProjectStateManager.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

int InitApplication();
void LoopApplication();
int EndApplication();

// アプリケーションの一番上になる StateManager.
std::auto_ptr< StateManagerBase > g_state_manager;

/**
	メイン関数.
*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow )
{
	//アプリケーションを初期化.
	if( InitApplication() == ApplicationFailure ){
		return ApplicationFailure;
	}
	//アプリケーションのループ.
	LoopApplication();
	//アプリケーションの終了処理.
	return EndApplication();
}

int InitApplication()
{
    g_state_manager.reset( new_ProjectStateManager() );
    g_state_manager->ChangeState( ProjectState_Battle );
    
    SingletonInputMouse::Init();
    SingletonImageLoader::Init();

    SetGraphMode( 640 , 480 , 16 ) ;
    ChangeWindowMode( TRUE ) ;
    if( DxLib_Init() == ApplicationFailure ){
		return ApplicationFailure;
	}
	SetDrawScreen( DX_SCREEN_BACK );

	//フォントサイズ設定.
	int const font_size = 12;
    SetFontSize( font_size );
	
	//初期化成功.
    return ApplicationSuccess;
}

void LoopApplication()
{
    while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
    {
    	SingletonInputMouse::Update();
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
