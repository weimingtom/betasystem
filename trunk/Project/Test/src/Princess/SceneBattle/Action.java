
class Action
{
    //アクションの種類.
    final int Type_Attack   = 0;
    final int Type_Deffence = 1;
    final int Type_Magic    = 2;
    
    //勝負結果.
    final int Result_Win    = 0;
    final int Result_Lose   = 1;
    final int Result_Drow   = 2;
    
    static int BattleResult( int player , int enemy )
    {
        if( player == enemy ){ return Result_Drow; }
        switch( player )
        {
        case Type_Attack:
            if( enemy == Type_Deffence )
            {
                return Result_Lose;
            }else{
                return Result_Win;
            }
        case Type_Deffence:
            if( enemy == Type_Attack )
            {
                return Result_Win;
            }else{
                return Result_Lose;
            }
        case Type_Magic:
            if( enemy == Type_Deffence )
            {
                return Result_Lose;
            }else{
                return Result_Win;
            }
        }
    }
};

/*使用構想.

if( Select )
{
    //勝負判定
    int result = Action.ResultOf( m_player_action_list[index].type , m_enemy_action_list[index].type );
    //結果に応じた行動.
    if( result == Result_Win )
    {
        Attack();
    }else if( result == Result_Lose ){
        Damage();
    }
    //切り替え.
    EndTurn();
}

*/

