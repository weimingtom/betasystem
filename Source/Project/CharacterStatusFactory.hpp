#ifndef include_0778b661_abda_4dfe_82d3_a2b34d15fea9
#define include_0778b661_abda_4dfe_82d3_a2b34d15fea9

#include "Project/CharacterStatus.hpp"

enum CharaType
{
    CharaType_Player,
    CharaType_GreenSlime,
    CharaType_BigGreenSlime,
};

CharacterStatus CharacterStatusOf( CharaType type );


#endif // include_0778b661_abda_4dfe_82d3_a2b34d15fea9

