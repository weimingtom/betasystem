#include "System/AnimFormat.hpp"

/**
	�v���W�F�N�g�Ŏg�p����A�S�ẴA�j���[�V�����f�[�^(���ł�).
*/
AnimFormat const gAnimData[ AnimType_Num ] =
{
	{ 2, 0, 0, 100, 100, 5, -1 }
	{ 2, 0, 0, 100, 100, 5, -1 }
};

AnimFormat const& AnimDataOf( AnimType anim_type )
{
	return gAnimData[anim_type];
}


