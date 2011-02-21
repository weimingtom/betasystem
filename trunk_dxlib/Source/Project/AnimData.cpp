#include "AnimData.hpp"

#include "System/AnimFormat.hpp"

/**
	�v���W�F�N�g�Ŏg�p����A�S�ẴA�j���[�V�����f�[�^(���ł�).
*/
AnimFormat const gAnimData[ AnimType_Num ] =
{
    //  ����,   x,  y,  width,  height, �\������,   ���[�v��
	{   2,      0,  0,    100,    150,    20,         AnimFormat::InfinityLoop },
	{   2,      0,  150,  100,    150,    10,         AnimFormat::InfinityLoop },
	{   2,      0,  0,    100,    100,    30,         AnimFormat::InfinityLoop },
};

AnimFormat const& AnimDataOf( AnimType anim_type )
{
	return gAnimData[anim_type];
}

