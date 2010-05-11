
class ActionFactory
{
    static final int ActionType_Attack = 0;
    static final int ActionType_Guard = 1;
    static final int ActionType_Recovery = 2;
    static final int ActionType_Num = 3;
    String m_name;
    
    static ActionBase new_Action( int action_type )
    {
        switch( action_type )
        {
        case ActionType_Attack:
            return new ActionAttack("Attack");
        case ActionType_Guard:
            return new ActionGuard("Guard");
        case ActionType_Recovery:
            return new ActionRecovery("Recovery");
        }
        return null;
    }
};

abstract class ActionBase
{
    String m_name;
    ActionBase( String name )
    {
        m_name = name;
    }
    abstract void Action( SceneBattleObjects objects );
};

class ActionAttack extends ActionBase
{
    ActionAttack( String name )
    {
        super( name );
    }
    void Action( SceneBattleObjects objects )
    {
        objects.m_damage_printer.Begin( objects.m_player.m_attack , true );
        objects.m_enemy.m_hp -= objects.m_player.m_attack;
        objects.m_enemy.m_hp =
            Range.Clamp( 0 , objects.m_enemy.m_hp , objects.m_enemy.m_hp_max );
    }
};

class ActionGuard extends ActionBase
{
    ActionGuard( String name )
    {
        super( name );
    }
    void Action( SceneBattleObjects objects )
    {
    }
};

class ActionRecovery extends ActionBase
{
    ActionRecovery( String name )
    {
        super( name );
    }
    void Action( SceneBattleObjects objects )
    {
        objects.m_player.m_hp += 10;
        objects.m_player.m_hp =
            Range.Clamp( 0 , objects.m_player.m_hp , objects.m_player.m_hp_max );
    }
};

