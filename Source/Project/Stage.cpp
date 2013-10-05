#include "Stage.hpp"

StageInfo gStageInfo[StageType_Num] =
{
    {
        "ステージ１",
        3000,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
    },
    {
        "ステージ２",
        3000,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
    },
    {
        "ステージ３",
        3000,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
    },
    {
        "ステージ４",
        3000,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
    },
    {
        "ステージ５",
        3000,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
    },
    {
        "ステージ６",
        3000,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
    },
};


StageInfo StageInfoOf( StageType type )
{
    return gStageInfo[type];
}

