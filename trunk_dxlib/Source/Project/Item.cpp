#include "Item.hpp"

char const* NameOf( ItemType type )
{
    static char const* item[ItemType_Num] =
    {
        "なし",
        "スライムの肉",
        "スライムの上質な肉",
        "生命の雫",
        "レッドマナストーン",
        "グリーンマナストーン",
        "ブルーマナストーン",
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
