#include "Item.hpp"

char const* NameOf( ItemType type )
{
    static char const* item[ItemType_Num] =
    {
        "�Ȃ�",
        "�X���C���̓�",
        "�X���C���̏㎿�ȓ�",
        "�����̎�",
        "���b�h�}�i�X�g�[��",
        "�O���[���}�i�X�g�[��",
        "�u���[�}�i�X�g�[��",
    };
	return item[type];
}

int DropPamiriado( ItemType type )
{
    static int list[ItemType_Num] =
    {
        0,
        500,
        250,
        20,
        100,
        100,
        100,
    };
    return list[type];
}
