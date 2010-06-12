#include "DxLibWrapper.hpp"

#include <memory>
#include "System/StateBase.hpp"
#include "Project/StateGameMain.hpp"

std::auto_ptr< StateBase > g_state;

int InitApplication()
{
	SetGraphMode( 640 , 480 , 16 ) ;
	ChangeWindowMode( TRUE ) ;
	if( DxLib_Init() == ApplicationFailure ) { return ApplicationFailure; }
	
	SetDrawScreen( DX_SCREEN_BACK );

	g_state.reset( new_StateGameMain() );

	return ApplicationSuccess;
}

void LoopApplication()
{
	while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
	{
		g_state->Update();
		
		ClearDrawScreen() ;	// ��ʂ�����������
		
		g_state->Draw();

		ScreenFlip() ;	// ����ʂ̓��e��\��ʂɔ��f������
	}
}

int EndApplication()
{
	DxLib_End();
	return ApplicationSuccess;
}

