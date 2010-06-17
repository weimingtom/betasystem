#ifndef include_3108f83f_5fbe_43f0_831a_bbfccc61e79a
#define include_3108f83f_5fbe_43f0_831a_bbfccc61e79a

#include "Project/AttackType.hpp"

class Character
{
public:
    static int const Action_Num = 3;
public:
    Character();
public:
    AttackType GetAction( int index );
public:
    int m_hp;
    int m_hp_max;
    int m_attack;
    int m_exp;
    static int const m_exp_max = 100;
    AttackType m_action[ Action_Num ];
    AttackType m_action_next;
};

#endif

