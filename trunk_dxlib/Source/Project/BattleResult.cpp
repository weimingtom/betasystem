#include "Project/BattleResult.hpp"

#include <assert.h>

BattleResult BattleResultOf( AttackType player , AttackType enemy )
{
    if( player == enemy ){ return BattleResult_Draw; }
    
    switch( player )
    {
    case AttackType_Sword:
        if( enemy == AttackType_Shield )
        {
            return BattleResult_Lose;
        }else{
            return BattleResult_Win;
        }
        break;
    case AttackType_Shield:
        if( enemy == AttackType_Magic )
        {
            return BattleResult_Lose;
        }else{
            return BattleResult_Win;
        }
        break;
    case AttackType_Magic:
        if( enemy == AttackType_Sword )
        {
            return BattleResult_Lose;
        }else{
            return BattleResult_Win;
        }
        break;
    }
    assert( !"BattleResult Nothing" );
    return BattleResult_Draw; // åxçêâÒî.
}
