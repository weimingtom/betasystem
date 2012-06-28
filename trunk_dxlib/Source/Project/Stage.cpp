#include "Stage.hpp"

StageInfo gStageInfo[StageType_Num] =
{
    {
        "�X�R�A�A�^�b�N�̐X",
        100,
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
        "�X���C���̐X�Q",
        100,
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
        "�X���C���̐X�R",
        100,
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

