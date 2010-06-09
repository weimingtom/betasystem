#include "DxLibWrapper/DxLibWrapper.hpp"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow )
{
	if( InitApplication() == ApplicationFailure ) { return ApplicationFailure ; }
	LoopApplication();
	return EndApplication();
}


