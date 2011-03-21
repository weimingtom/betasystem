#include "Item.hpp"

char const* NameOf( ItemType type )
{
    static char const* item[ItemType_Num] =
    {
        "�Ȃ�",
        "�X���C���̓�",
        "�X���C���̏㎿�ȓ�",
        "�����̎�",
    };
	return item[type];
}

int DropPamiriado( ItemType type )
{
    static int list[ItemType_Num] =
    {
        0,
        160,
        40,
        2,
    };
    return list[type];
}
