#ifndef include_92f9d2ae_f761_4a91_9473_5a817611cef7
#define include_92f9d2ae_f761_4a91_9473_5a817611cef7

#include "limits.h"
#include "DxLib.h"

inline int GetRandToMax( int max )
{
    return GetRand( max - 1 );
}

inline int GetRand()
{
    return GetRand( INT_MAX );
}

//! ”ÍˆÍŽw’è.
inline int GetRand( int min, int max )
{
    int const diff = max - min;
    return ( min + GetRand(diff) );
}

#endif

