#include "Project/CharacterStatusFactory.hpp"

CharacterStatus CharacterStatusOf( CharaType type )
{
    switch( type )
    {
    case CharaType_Player:
        return CharacterStatus( 3 , 1 , 0 );
    case CharaType_GreenSlime:
        return CharacterStatus( 3 , 1 , 0 );
    case CharaType_BigGreenSlime:
        return CharacterStatus( 5 , 1 , 0 );
    default:
        return CharacterStatus( 0 , 0 , 0 );
    }
}

