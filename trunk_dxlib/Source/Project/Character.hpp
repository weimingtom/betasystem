#ifndef include_3108f83f_5fbe_43f0_831a_bbfccc61e79a
#define include_3108f83f_5fbe_43f0_831a_bbfccc61e79a

#include "Project/AttackType.hpp"

class Character
{
public:
    Character();
    Character( int hp_max , int attack , int exp )
     : m_hp_max( hp_max )
     , m_attack( attack )
     , m_exp( exp )
    {
        m_hp = m_hp_max;
    }
    
public:
    int m_hp;
    int m_hp_max;
    int m_attack;
    int m_exp;
    static int const m_exp_max = 100;
};

#endif

