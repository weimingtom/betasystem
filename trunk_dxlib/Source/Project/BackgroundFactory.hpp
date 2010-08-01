#ifndef include_21ea25ad_d634_4f8d_b036_992bdff1daf9
#define include_21ea25ad_d634_4f8d_b036_992bdff1daf9

enum BackgroundType
{
    BackgroundType_Forest,
    BackgroundType_RedForest,
};

void SetBackground( BackgroundType type );

BackgroundType GetBackground();

#endif

