#include "System/Range.hpp"

bool Range( int min , int var , int max )
{
    if( min <= var && var <= max )
    {
        return true;
    }
    return false;
}

