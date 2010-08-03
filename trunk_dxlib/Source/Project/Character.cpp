#include "Project/Character.hpp"

Character::Character( int hp_max , int attack , int exp )
 : m_hp_max( hp_max )
 , m_attack( attack )
 , m_exp( exp )
{
    m_hp = m_hp_max;
}

