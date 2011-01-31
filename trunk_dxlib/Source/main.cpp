#include "DxLibWrapper/DxLibWrapper.hpp"

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


