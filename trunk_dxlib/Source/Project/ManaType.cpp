#include "ManaType.hpp"

char const* NameOf(ManaType mana_type)
{
    char const* name[ManaType_Num] = {
        "��",
        "��",
        "��",
    };
    return name[mana_type];
}

