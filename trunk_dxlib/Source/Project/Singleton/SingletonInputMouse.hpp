#ifndef include_b122a87f_b25d_4192_b94d_5e7589771cd3
#define include_b122a87f_b25d_4192_b94d_5e7589771cd3

#include "DxLibWrapper/InputMouse.hpp"

/**
	�v���W�F�N�g�B��̃}�E�X�C���^�[�t�F�[�X.
*/
namespace SingletonInputMouse
{
	/**
		������.
	*/
	void Init();
	/**
		�X�V.
	*/
	void Update();
	/**
		�C���X�^���X�̎擾.
	*/
	InputMouse* Get();
};

#endif // include_b122a87f_b25d_4192_b94d_5e7589771cd3
