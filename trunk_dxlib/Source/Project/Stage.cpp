#include "Stage.hpp"

StageInfo gStageInfo[StageType_Num] =
{
    {
        "ƒXƒ‰ƒCƒ€‚ÌX‚P",
        100,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        0,
        0,
        0,
        0,
        0,
        Enemy::Type_GreenSlime,
    },
    {
        "ƒXƒ‰ƒCƒ€‚ÌX‚Q",
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
        "ƒXƒ‰ƒCƒ€‚ÌX‚R",
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

