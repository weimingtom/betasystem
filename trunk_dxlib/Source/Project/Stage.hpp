#ifndef include_stage_hpp
#define include_stage_hpp

#include "Enemy.hpp"

static int const EnemyPointMax = 5;

/**
    ステージ情報.
*/
struct StageInfo{
    char const* name;							//!< ステージ名.
    int total_enemy;							//!< 総敵数.
    Enemy::Type change_enemy[EnemyPointMax];	//!< ザコ敵の種類.
    int change_point[EnemyPointMax];			//!< ザコ敵が切り替わるポイント.
    Enemy::Type boss;							//!< ボスの種類.
};

/**
    ステージの種類.
*/
enum StageType{
    StageType_ScoreAttack,
    StageType_RedForest,
    StageType_WhiteForest,
    StageType_4,
    StageType_5,
    StageType_Dummy,
    StageType_Num
};

/**
    ステージ情報取得.
*/
StageInfo StageInfoOf( StageType type );

#endif // include_stage_hpp

