#include "Project/AttackType.hpp"

char const* NameOf( AttackType type )
{
    static const char* name[ AttackType_Num ] =
    {
        "UŒ‚",
        "•KE",
        "–hŒä",
    };
    return name[ type ];
}

int NeedPointOf( AttackType attack_type )
{
    switch( attack_type  )
    {
    case AttackType_Normal:
        return 1;
        break;
    case AttackType_Special:
        return 2;
        break;
    case AttackType_Guard:
        return -1;
        break;
    }
}

