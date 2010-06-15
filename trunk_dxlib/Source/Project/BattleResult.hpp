#ifndef include_guard_uuid_9e508b6c_ee06_4553_b04f_fef78fd968df
#define include_guard_uuid_9e508b6c_ee06_4553_b04f_fef78fd968df

#include "Project/AttackType.hpp"

/**
    戦闘結果.
*/
enum BattleResult
{
    BattleResult_Win,
    BattleResult_Lose,
    BattleResult_Draw,
};

/**
    戦闘結果を返す関数.
    @param player プレイヤーの攻撃タイプ.
    @param enemy 敵の攻撃タイプ.
*/
BattleResult BattleResultOf( AttackType player , AttackType enemy );

#endif
