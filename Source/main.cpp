#include <DxLib.h>
#include "DxLibWrapper/ReturnVariable.hpp"
#include <memory>
#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "Project/Singleton/SingletonStateManager.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "../Resource/resource.h"


//! FPS表示.
void FpsTimeFanction(){

	static int counter=0,FpsTime[2]={0,},FpsTime_i=0;
	static double Fps=0.0;
	static char Key[256];

        if(FpsTime_i== 0)
                FpsTime[0]=GetNowCount();               //1周目の時間取得
        if(FpsTime_i==49){
                FpsTime[1]=GetNowCount();               //50周目の時間取得
                Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//測定した値からfpsを計算
                FpsTime_i=0;//カウントを初期化
        }
        else
                FpsTime_i++;//現在何周目かカウント
        if(Fps != 0)
                DrawFormatString(565,460,GetColor(255,255,255),"FPS %.1f",Fps); //fpsを表示
        return;
}


//! シングルトンの初期化.
void InitSingleton()
{
    SingletonInputMouse::Init();
    PrincessImageLoader::Init();
    SingletonSoundLoader::Init();
    Singleton::InitKeyInput();
	Princess::StateManager::GetInstance();
}

//! DxLib関係の設定.
//! @return 失敗したらApplicationFailureを返す.
int SetConfigDxLib()
{
	
    SetMainWindowText("PrincessCrave");

	#ifdef _DEBUG
    	SetMainWindowText("PrincessCrave:DebugBuild");
    #endif

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
        if( CheckHitKey( KEY_INPUT_F1 ) != 0 ){
			Princess::StateManager::GetInstance()->ChangeState(
				Princess::StateManager::new_State( Princess::State_DebugTop )
			);
        }

        ClearDrawScreen() ;    // 画面クリア.
    
        //Update
    	SingletonInputMouse::Update();
		Singleton::UpdateKeyInput();
		Princess::StateManager::GetInstance()->Update();
        
        //Draw
		Princess::StateManager::GetInstance()->Draw();

		FpsTimeFanction();

        ScreenFlip() ;    // 裏画面の内容を表画面に反映させる
    }
}

void ReleaseSingleton()
{
    SingletonSoundLoader::Release();
    PrincessImageLoader::Release();
	Princess::StateManager::DeleteInstance();
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
