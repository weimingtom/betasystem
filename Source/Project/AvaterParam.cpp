#include "AvaterParam.hpp"

char const* NameOf(TypeOption type)
{
	static char const* name[Option_Num] =
	{
		"�Ȃ�",
		"�ዾ",
		"�X���C���ʂ������",
	};
	return name[type];
}
char const* NameOf(TypeCloth type)
{
	static char const* name[Cloth_Num] =
	{
		"�Z�[���[��",
		"���C�h��",
		"�p�[�J�[",
		"�s�V���c",
	};
	return name[type];
}
char const* NameOf(TypeFace type)
{
	static char const* name[Face_Num] =
	{
		"�����",
		"�W�g��",
		"�ނ��",
		"�A�z��",
	};
	return name[type];
}
char const* NameOf(TypeHairColor type)
{
	static char const* name[HairColor_Num] =
	{
		"��",
		"��",
		"��",
		"��",
		"���F",
	};
	return name[type];
}
char const* NameOf(TypeHair type)
{
	static char const* name[Hair_Num] =
	{
		"�����O",
		"�V���[�g",
		"�c�C���e�[��",
		"�|�j�[�e�[��",
	};
	return name[type];
}

