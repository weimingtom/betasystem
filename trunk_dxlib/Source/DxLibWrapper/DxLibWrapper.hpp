#ifndef include_d2462ad29a1f43779bf725389086fa3c
#define include_d2462ad29a1f43779bf725389086fa3c

#include "DxLib.h"

int const ApplicationSuccess = 0;
int const ApplicationFailure = -1;
int const FunctionFailure = -1;

int InitApplication();
void LoopApplication();
int EndApplication();

inline int DefaultFontColor()
{
    return GetColor( 200 , 255 , 200 );
}

#endif
