#include "Project/Character.hpp"
#include "DxLibWrapper/DxLibWrapper.hpp"

namespace {

    AttackType RandomAction()
{
    return static_cast< AttackType >( GetRandToMax( AttackType_Num ) );
}

}

Character::Character()
{
    m_hp_max = 20;
    m_hp = m_hp_max;
    m_attack = 5;
    m_exp = 0;
    for( int i = 0 ; i < AttackType_Num ; i++ )
    {
        m_action[i] = static_cast< AttackType >( i );
    }
    m_action_next = RandomAction();
}

AttackType Character::GetAction( int index )
{
    AttackType const result = m_action[index];
    m_action[index] = m_action_next;
    m_action_next = RandomAction();
    return result;
}


