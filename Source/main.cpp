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
    ProjectImageLoader::Init();
    SingletonSoundLoader::Init();
    Singleton::InitKeyInput();
	ProjectStateManager::GetInstance();
}

//! DxLib�֌W�̐ݒ�.
//! @return ���s������ApplicationFailure��Ԃ�.
int SetConfigDxLib()
{
    SetMainWindowText("PrincessCrave!");

    SetWindowIconID( IDI_ICON1 ); // DxLib_Init ���O�ł���K�v������.

    SetGraphMode( 640 , 480 , 16 ) ;

    ChangeWindowMode( TRUE ) ;

    if( DxLib_Init() == ApplicationFailure ){
		return ApplicationFailure;
	}
	SetDrawScreen( DX_SCREEN_BACK );

	//�t�H���g�T�C�Y�ݒ�.
	int const font_size = 14;
    SetFontSize( font_size );

    return ApplicationSuccess;
}

//! �A�v���P�[�V�����̏�����.
int InitApplication()
{
    int const result = SetConfigDxLib();
	if( result == ApplicationFailure ){
	    return ApplicationFailure;
	}
	
    InitSingleton();
    
    return ApplicationSuccess;
}

void MainLoopOfApplication()
{
    while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
    {
    	SingletonInputMouse::Update();
		Singleton::UpdateKeyInput();
    	ProjectStateManager::GetInstance()->Update();
        
        ClearDrawScreen() ;    // ��ʂ�����������
    	ProjectStateManager::GetInstance()->Draw();
        ScreenFlip() ;    // ����ʂ̓��e��\��ʂɔ��f������
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
    // Dxlib�̃n���h���������V���O���g��������̂ŁADxLib_End����ɂ��Ȃ���
    // Dxlib_End�̃n���h�������J���Ƌ������Ă��܂�.
    ReleaseSingleton();

    DxLib_End();

    return ApplicationSuccess;
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

	if( result == ApplicationFailure ){
		return ApplicationFailure;
	}

	MainLoopOfApplication();

	return ExitApplication();
}
