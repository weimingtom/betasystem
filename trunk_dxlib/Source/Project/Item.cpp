#include "Item.hpp"

char const* NameOf( ItemType type )
{
    static char const* item[ItemType_Num] =
    {
        "なし",
        "スライムの肉",
        "スライムの上質な肉",
        "生命の雫",
    };
	return item[type];
}

int DropPamiriado( ItemType type )
{
    static int list[ItemType_Num] =
    {
        0,
        80,
        20,
        1,
    };
    return list[type];
}
