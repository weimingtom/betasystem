#ifndef ENEMY_PARAM_HPP__
#define ENEMY_PARAM_HPP__

#include "Project/Item/ItemInfo.hpp"

struct EnemyParam
{
    int mHp;
    int mAttack;
    ItemInfo mEquipList[EquipPos_Num];
    int mDropPercent;
};

//! �GID.
enum EnemyID
{
    EnemyID_0,
    EnemyID_1,
    EnemyID_2,
};

//! �G�p�����[�^�̎擾.
EnemyParam EnemyParamOf(EnemyID enemy_id);

extern EnemyParam gEnemyParam;

#endif // save_data_hpp

