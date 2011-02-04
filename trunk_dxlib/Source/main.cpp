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

// �A�v���P�[�V�����̈�ԏ�ɂȂ� StateManager.
std::auto_ptr< StateManagerBase > g_state_manager;

/**
	���C���֐�.
*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow )
{
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

	//�t�H���g�T�C�Y�ݒ�.
	int const font_size = 12;
    SetFontSize( font_size );
	
	//����������.
    return ApplicationSuccess;
}

void LoopApplication()
{
    while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
    {
    	SingletonInputMouse::Update();
        g_state_manager->Update();
        
        ClearDrawScreen() ;    // ��ʂ�����������
        g_state_manager->Draw();
        ScreenFlip() ;    // ����ʂ̓��e��\��ʂɔ��f������
    }
}

int EndApplication()
{
    g_state_manager.reset(0);
    DxLib_End();
    return ApplicationSuccess;
}
