#include "DxLibWrapper/DxLibWrapper.hpp"

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


