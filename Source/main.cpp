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

//! �V���O���g���̏�����.
void InitSingleton()
{
    SingletonInputMouse::Init();
    PrincessImageLoader::Init();
    SingletonSoundLoader::Init();
    Singleton::InitKeyInput();
	Princess::ProjectStateManager::GetInstance();
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
			Princess::ProjectStateManager::GetInstance()->ChangeState(
				Princess::ProjectStateManager::new_State( Princess::ProjectStateManager::State_DebugTop )
			);
        }

        ClearDrawScreen() ;    // ��ʃN���A.
    
        //Update
    	SingletonInputMouse::Update();
		Singleton::UpdateKeyInput();
		Princess::ProjectStateManager::GetInstance()->Update();
        
        //Draw
		Princess::ProjectStateManager::GetInstance()->Draw();
        ScreenFlip() ;    // ����ʂ̓��e��\��ʂɔ��f������
    }
}

void ReleaseSingleton()
{
    SingletonSoundLoader::Release();
    PrincessImageLoader::Release();
	Princess::ProjectStateManager::DeleteInstance();
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
