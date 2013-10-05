#include "System/Range.hpp"

bool Range( int min , int var , int max )
{
    if( min <= var && var <= max )
    {
        return true;
    }
    return false;
}

int Clamp( int min , int var , int max )
{
    if( var <= min ){ return min; }
    if( var >= max ){ return max; }
    return var;
}


