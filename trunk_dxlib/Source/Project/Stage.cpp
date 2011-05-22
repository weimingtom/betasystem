#include "Stage.hpp"

StageInfo gStageInfo[StageType_Num] =
{
    {
        "スコアアタックの森",
        2000,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        0,
        1000,
        1500,
        0,
        0,
        Enemy::Type_GreenSlime,
    },
    {
        "スライムの森２",
        200,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        100,
        0,
        0,
        0,
        0,
        Enemy::Type_GreenSlime,
    },
    {
        "スライムの森３",
        400,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        100,
        200,
        300,
        0,
        0,
        Enemy::Type_GreenSlime,
    },
};


StageInfo StageInfoOf( StageType type )
{
    return gStageInfo[type];
}

