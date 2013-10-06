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
#include "Project/SaveData.hpp"

int InitApplication();
void LoopApplication();
int EndApplication();

/**
	���C���֐�.
*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow )
{
    SetMainWindowText("PrincessCrave!");
	//�A�v���P�[�V������������.
	if( InitApplication() == ApplicationFailure ){
		return ApplicationFailure;
	}
	//�A�v���P�[�V�����̃��[�v.
	LoopApplication();
	//�A�v���P�[�V�����̏I������.
	return EndApplication();
}

int InitApplication()
{
    SetWindowIconID( IDI_ICON1 ); //!< DxLib_Init ���O�ł���K�v������.

    SetGraphMode( 640 , 480 , 16 ) ;
    ChangeWindowMode( TRUE ) ;
    if( DxLib_Init() == ApplicationFailure ){
		return ApplicationFailure;
	}
	SetDrawScreen( DX_SCREEN_BACK );

	//�t�H���g�T�C�Y�ݒ�.
	int const font_size = 14;
    SetFontSize( font_size );
	
    //�V���O���g���̏�����.
    SingletonInputMouse::Init();
    SingletonImageLoader::Init();
    SingletonSoundLoader::Init();
    Singleton::InitKeyInput();
	ProjectStateManager::GetInstance();
    
	//����������.
    return ApplicationSuccess;
}

void LoopApplication()
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

int EndApplication()
{
    /*
        DxLib_End����낾�ƁA��������̃f�[�^�̊J���Ɏ��s����̂ŁA��O�ŊJ��.
    */
    SingletonSoundLoader::Release();
    SingletonImageLoader::Release();
    DxLib_End();
    return ApplicationSuccess;
}
