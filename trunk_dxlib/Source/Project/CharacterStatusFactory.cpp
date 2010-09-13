#include "Project/CharacterStatusFactory.hpp"

CharacterStatus CharacterStatusOf( CharaType type )
{
    switch( type )
    {
    case CharaType_Player:
        return CharacterStatus( 15 , 4 , 0 );
    case CharaType_GreenSlime:
        return CharacterStatus( 5 , 2 , 50 );
    case CharaType_BigGreenSlime:
        return CharacterStatus( 10 , 4 , 50 );
    default:
        return CharacterStatus( 0 , 0 , 0 );
    }
}

