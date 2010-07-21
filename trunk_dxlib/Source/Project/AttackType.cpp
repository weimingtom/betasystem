#include "Project/AttackType.hpp"

char const* NameOf( AttackType type )
{
    static const char* name[ AttackType_Num ] =
    {
        "Œ•",
        "‚",
        "–‚–@",
    };
    return name[ type ];
}

