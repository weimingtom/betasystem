#ifndef include_21e97407_aadb_4abc_882f_2c4a55ee2b26
#define include_21e97407_aadb_4abc_882f_2c4a55ee2b26

/**
    UŒ‚s“®‚ÉŠÖ‚µ‚Ä‚Ìî•ñ‚ğ•Û‚·‚éƒNƒ‰ƒX.
*/
class AttackContent
{
public:
    static int const Action_Num = 3;
public:
    AttackContent()
    {
        for( int i = 0 ; i < AttackType_Num ; i++ )
        {
            m_action[i] = static_cast< AttackType >( i );
        }
        m_action_next = RandomAction();
    };
public:
    AttackType GetAction( int index )
    {
        AttackType const result = m_action[index];
        m_action[index] = m_action_next;
        m_action_next = RandomAction();
        return result;
    }
    AttackType RandomAction()
    {
        return static_cast< AttackType >( GetRandToMax( AttackType_Num ) );
    }
public:
    AttackType m_action[ Action_Num ];
    AttackType m_action_next;
};

#endif // include_21e97407_aadb_4abc_882f_2c4a55ee2b26

