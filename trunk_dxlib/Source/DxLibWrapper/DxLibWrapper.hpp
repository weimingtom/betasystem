#ifndef include_d2462ad29a1f43779bf725389086fa3c
#define include_d2462ad29a1f43779bf725389086fa3c

#include "DxLib.h"

int const ApplicationSuccess = 0;
int const ApplicationFailure = -1;
int const FunctionFailure = -1;

int InitApplication();
void LoopApplication();
int EndApplication();

inline int ColorOf( int r = 0 , int g = 0 , int b = 0 )
{
    return GetColor( r , g , b );
}

inline int GetRandToMax( int max )
{
    return GetRand( max - 1 );
}

class Vector2;
void DrawGraph( int x , int y , int image_handle );
void DrawGraph( Vector2 pos , int image_handle );

#endif
