#ifndef include_3108f83f_5fbe_43f0_831a_bbfccc61e79a
#define include_3108f83f_5fbe_43f0_831a_bbfccc61e79a

#include "Project/AttackType.hpp"

struct Character
{
    int m_hp;
    int m_hp_max;
    int m_attack;
    int m_exp;
    static int const m_exp_max = 100;
    static int const Action_Num = 3;
    AttackType m_action[ Action_Num ];
    AttackType m_action_next;
    
    Character()
    {
        m_hp_max = 20;
        m_hp = m_hp_max;
        m_attack = 5;
        m_exp = 0;
        for( int i = 0 ; i < AttackType_Num ; i++ )
        {
            m_action[i] = static_cast< AttackType >( i );
        }
        m_action_next = static_cast< AttackType >( GetRandToMax( AttackType_Num ) );
    }
};

#endif

