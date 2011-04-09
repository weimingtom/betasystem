#ifndef include_stage_hpp
#define include_stage_hpp

#include "Enemy.hpp"

static int const EnemyPointMax = 5;

/**
    �X�e�[�W���.
*/
struct StageInfo{
    char const* name;
    int total_enemy;
    Enemy::Type change_enemy[EnemyPointMax];
    int change_point[EnemyPointMax];
    Enemy::Type boss;
};

/**
    �X�e�[�W�̎��.
*/
enum StageType{
    StageType_ScoreAttack,
    StageType_RedForest,
    StageType_WhiteForest,
    StageType_Num
};

/**
    �X�e�[�W���擾.
*/
StageInfo StageInfoOf( StageType type );

#endif // include_stage_hpp

