#include "Project/AttackType.hpp"

char const* NameOf( AttackType type )
{
    static const char* name[ AttackType_Num ] =
    {
        "�U��",
        "�K�E",
        "�h��",
    };
    return name[ type ];
}
