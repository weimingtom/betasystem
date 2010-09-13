#ifndef include_34393d03_1996_4322_a288_9d3a0b102c03
#define include_34393d03_1996_4322_a288_9d3a0b102c03

#include "System/String.hpp"

enum SoundType
{
    SoundType_WorldMap,
    SoundType_Decide,
    SoundType_OnButton,
    SoundType_ReleaseButton,
    SoundType_Attack,
    SoundType_Num,
};

String NameOf( SoundType type );

StringList SoundFileList();

#endif

