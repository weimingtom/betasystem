#ifndef include_guard_uuid_9e508b6c_ee06_4553_b04f_fef78fd968df
#define include_guard_uuid_9e508b6c_ee06_4553_b04f_fef78fd968df

#include "Project/AttackType.hpp"

/**
    �퓬����.
*/
enum BattleResult
{
    BattleResult_Win,
    BattleResult_Lose,
    BattleResult_Draw,
};

/**
    �퓬���ʂ�Ԃ��֐�.
    @param player �v���C���[�̍U���^�C�v.
    @param enemy �G�̍U���^�C�v.
*/
BattleResult BattleResultOf( AttackType player , AttackType enemy );

#endif
