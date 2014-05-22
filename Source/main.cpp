#include <DxLib.h>
#include "DxLibWrapper/ReturnVariable.hpp"
#include <memory>
#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "System/StateManagerBase.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "../Resource/resource.h"

//! シングルトンの初期化.
void InitSingleton()
{
    SingletonInputMouse::Init();
    ProjectImageLoader::Init();
    SingletonSoundLoader::Init();
    Singleton::InitKeyInput();
	ProjectStateManager::GetInstance();
}

//! DxLib関係の設定.
//! @return 失敗したらApplicationFailureを返す.
int SetConfigDxLib()
{
    SetMainWindowText("PrincessCrave!");

    SetWindowIconID( IDI_ICON1 ); // DxLib_Init より前である必要がある.

    SetGraphMode( 640 , 480 , 16 ) ;

    ChangeWindowMode( TRUE ) ;

    int const kInitResult = DxLib_Init();
    if( kInitResult == DxLib_Failure ){
		return DxLib_Failure;
	}
	SetDrawScreen( DX_SCREEN_BACK );

    return DxLib_Success;
}

//! アプリケーションの初期化.
int InitApplication()
{
    int const result = SetConfigDxLib();
	if( result == DxLib_Failure ){
	    return DxLib_Failure;
	}
	
    InitSingleton();
    
    return DxLib_Success;
}

//! メインループ.
void MainLoopOfApplication()
{
    while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
    {
        //Update
    	SingletonInputMouse::Update();
		Singleton::UpdateKeyInput();
    	ProjectStateManager::GetInstance()->Update();
        
        //Draw
        ClearDrawScreen() ;    // 画面クリア.
    	ProjectStateManager::GetInstance()->Draw();
        ScreenFlip() ;    // 裏画面の内容を表画面に反映させる
    }
}

void ReleaseSingleton()
{
    SingletonSoundLoader::Release();
    ProjectImageLoader::Release();
    ProjectStateManager::DeleteInstance();

}

int ExitApplication()
{
    // Dxlibのハンドルを扱うシングルトンがあるので、DxLib_Endより先にやらないと
    // Dxlib_Endのハンドル自動開放と競合してしまう.
    ReleaseSingleton();

    DxLib_End();

    return DxLib_Success;
}

/**
	メイン関数.
*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow )
{
    int const result = InitApplication();

	if( result == DxLib_Failure ){
		return DxLib_Failure;
	}

	MainLoopOfApplication();

	return ExitApplication();
}
