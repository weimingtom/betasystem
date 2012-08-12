#include "Stage.hpp"

StageInfo gStageInfo[StageType_Num] =
{
    {
        "�X�e�[�W�P",
        3000,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
    },
    {
        "�X�e�[�W�Q",
        3000,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
    },
    {
        "�X�e�[�W�R",
        3000,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
    },
    {
        "�X�e�[�W�S",
        3000,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
    },
    {
        "�X�e�[�W�T",
        3000,
        Enemy::Type_RedSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_SteelSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
        Enemy::Type_GreenSlime,
    },
    {
        "�X�e�[�W�U",
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

