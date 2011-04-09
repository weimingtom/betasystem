#ifndef include_stage_hpp
#define include_stage_hpp

#include "Enemy.hpp"

static int const EnemyPointMax = 5;

/**
    ステージ情報.
*/
struct StageInfo{
    char const* name;
    int total_enemy;
    Enemy::Type change_enemy[EnemyPointMax];
    int change_point[EnemyPointMax];
    Enemy::Type boss;
};

/**
    ステージの種類.
*/
enum StageType{
    StageType_ScoreAttack,
    StageType_RedForest,
    StageType_WhiteForest,
    StageType_Num
};

/**
    ステージ情報取得.
*/
StageInfo StageInfoOf( StageType type );

#endif // include_stage_hpp

