#include "Item.hpp"

char const* NameOf( ItemType type )
{
    static char const* item[ItemType_Num] =
    {
        "スライムの肉",
        "スライムの水",
    };
	return item[type];
}

