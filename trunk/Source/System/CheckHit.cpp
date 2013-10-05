#include "System/CheckHit.hpp"
#include "System/Vector2.hpp"

/**
    “_‚Æ‹éŒ`.
*/
bool CheckHitRect( Vector2 pos_1 , Vector2 pos_2 , Vector2 size_2 )
{
    if(
        pos_1.x < pos_2.x
        || pos_1.y < pos_2.y
        || pos_1.x > pos_2.x + size_2.x
        || pos_1.y > pos_2.y + size_2.y
    )
    {
        return false;
    }
    return true;
}

