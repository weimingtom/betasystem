#include "Item.hpp"

char const* NameOf( ItemType type )
{
    static char const* item[ItemType_Num] =
    {
        "�Ȃ�",
        "�X���C���̓�",
        "�X���C���̐�",
    };
	return item[type];
}

