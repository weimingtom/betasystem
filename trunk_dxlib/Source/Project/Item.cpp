#include "Item.hpp"

char const* NameOf( ItemType type )
{
    static char const* item[ItemType_Num] =
    {
        "‚È‚µ",
        "“÷",
        "–‚Î",
        "¶–½‚Ì´",
    };
	return item[type];
}

int DropPamiriado( ItemType type )
{
    static int list[ItemType_Num] =
    {
        0,
        50,
        10,
        10,
    };
    return list[type];
}
