#include "Stage.hpp"

StageInfo gStageInfo[StageType_Num] =
{
    {
        "òrééÇµÇÃêX",
        100,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        0,
        80,
        1500,
        9999,
        9999,
        Enemy::Type_GreenSlime,
    },
    {
        "ÉXÉâÉCÉÄÇÃêX",
        200,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_RedSlime,
        0,
        150,
        250,
        9999,
        9999,
        Enemy::Type_GreenSlime,
    },
    {
        "ÉXÉâÉCÉÄÇÃêXÇR",
        300,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        100,
        200,
        250,
        9999,
        9999,
        Enemy::Type_GreenSlime,
    },
    {
        "É_É~Å[",
        300,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        100,
        200,
        250,
        9999,
        9999,
        Enemy::Type_GreenSlime,
    },
};


StageInfo StageInfoOf( StageType type )
{
    return gStageInfo[type];
}

