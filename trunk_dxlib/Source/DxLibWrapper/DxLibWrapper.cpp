#include "DxLibWrapper.hpp"

#include <memory>
#include "System/StateBase.hpp"
#include "Application/StateMouseInput.hpp"

std::auto_ptr< StateBase > g_state;

int InitApplication()
{
	SetGraphMode( 640 , 480 , 16 ) ;
	ChangeWindowMode( TRUE ) ;
	if( DxLib_Init() == ApplicationFailure ) { return ApplicationFailure; }
	
	SetDrawScreen( DX_SCREEN_BACK );

	g_state.reset( new_StateMouseInput() );

	return ApplicationSuccess;
}

void LoopApplication()
{
	while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
	{
		g_state->Update();
		
		ClearDrawScreen() ;	// 画面を初期化する
		
		g_state->Draw();

		ScreenFlip() ;	// 裏画面の内容を表画面に反映させる
	}
}

int EndApplication()
{
	DxLib_End();
	return ApplicationSuccess;
}

