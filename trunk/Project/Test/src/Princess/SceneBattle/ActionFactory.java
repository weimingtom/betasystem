
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
            return new ActionRecovery("Magic");
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
};

class ActionAttack extends ActionBase
{
    ActionAttack( String name )
    {
        super( name );
    }
};

class ActionGuard extends ActionBase
{
    ActionGuard( String name )
    {
        super( name );
    }
};

class ActionRecovery extends ActionBase
{
    ActionRecovery( String name )
    {
        super( name );
    }
};

