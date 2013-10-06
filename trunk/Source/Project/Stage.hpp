#ifndef include_stage_hpp
#define include_stage_hpp

#include "Enemy.hpp"

static int const EnemyPointMax = 5;

/**
    �X�e�[�W���.
*/
struct StageInfo{
    char const* name;							//!< �X�e�[�W��.
    int length;							        //!< �X�e�[�W�̒���.
    Enemy::Type change_enemy[EnemyPointMax];	//!< �U�R�G�̎��.
    Enemy::Type boss;							//!< �{�X�̎��.
};

/**
    �X�e�[�W�̎��.
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
    �X�e�[�W���擾.
*/
StageInfo StageInfoOf( StageType type );

#endif // include_stage_hpp
