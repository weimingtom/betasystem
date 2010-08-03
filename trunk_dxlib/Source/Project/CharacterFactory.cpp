#include "Project/CharacterFactory.hpp"

Character CharacterOf( CharaType type )
{
    switch( type )
    {
    case CharaType_Player:
        return Character( 15 , 4 , 0 );
    case CharaType_GreenSlime:
        return Character( 5 , 2 , 50 );
    case CharaType_BigGreenSlime:
        return Character( 10 , 4 , 50 );
    default:
        return Character( 0 , 0 , 0 );
    }
}

