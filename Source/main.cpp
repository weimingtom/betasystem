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


//! FPS�\��.
void FpsTimeFanction(){

	static int counter=0,FpsTime[2]={0,},FpsTime_i=0;
	static double Fps=0.0;
	static char Key[256];

        if(FpsTime_i== 0)
                FpsTime[0]=GetNowCount();               //1���ڂ̎��Ԏ擾
        if(FpsTime_i==49){
                FpsTime[1]=GetNowCount();               //50���ڂ̎��Ԏ擾
                Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//���肵���l����fps���v�Z
                FpsTime_i=0;//�J�E���g��������
        }
        else
                FpsTime_i++;//���݉����ڂ��J�E���g
        if(Fps != 0)
                DrawFormatString(565,460,GetColor(255,255,255),"FPS %.1f",Fps); //fps��\��
        return;
}


//! �V���O���g���̏�����.
void InitSingleton()
{
    SingletonInputMouse::Init();
    PrincessImageLoader::Init();
    SingletonSoundLoader::Init();
    Singleton::InitKeyInput();
	Princess::StateManager::GetInstance();
}

//! DxLib�֌W�̐ݒ�.
//! @return ���s������ApplicationFailure��Ԃ�.
int SetConfigDxLib()
{
	
    SetMainWindowText("PrincessCrave");

	#ifdef _DEBUG
    	SetMainWindowText("PrincessCrave:DebugBuild");
    #endif

    SetWindowIconID( IDI_ICON1 ); // DxLib_Init ���O�ł���K�v������.

    SetGraphMode( 640 , 480 , 16 ) ;

    ChangeWindowMode( TRUE ) ;

    int const kInitResult = DxLib_Init();
    if( kInitResult == DxLib_Failure ){
		return DxLib_Failure;
	}
	SetDrawScreen( DX_SCREEN_BACK );

    return DxLib_Success;
}

//! �A�v���P�[�V�����̏�����.
int InitApplication()
{
    int const result = SetConfigDxLib();
	if( result == DxLib_Failure ){
	    return DxLib_Failure;
	}
	
    InitSingleton();
    
    return DxLib_Success;
}

//! ���C�����[�v.
void MainLoopOfApplication()
{
    while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
    {
        if( CheckHitKey( KEY_INPUT_F1 ) != 0 ){
			Princess::StateManager::GetInstance()->ChangeState(
				Princess::StateManager::new_State( Princess::State_DebugTop )
			);
        }

        ClearDrawScreen() ;    // ��ʃN���A.
    
        //Update
    	SingletonInputMouse::Update();
		Singleton::UpdateKeyInput();
		Princess::StateManager::GetInstance()->Update();
        
        //Draw
		Princess::StateManager::GetInstance()->Draw();

		FpsTimeFanction();

        ScreenFlip() ;    // ����ʂ̓��e��\��ʂɔ��f������
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
    // Dxlib�̃n���h���������V���O���g��������̂ŁADxLib_End����ɂ��Ȃ���
    // Dxlib_End�̃n���h�������J���Ƌ������Ă��܂�.
    ReleaseSingleton();

    DxLib_End();

    return DxLib_Success;
}

/**
	���C���֐�.
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
