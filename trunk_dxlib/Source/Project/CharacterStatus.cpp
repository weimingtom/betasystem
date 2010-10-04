#include "Project/CharacterStatus.hpp"
#include "DxLibWrapper/Random.hpp"

namespace{

static int const s_default_exp_max = 100;

}//namespace unnamed

CharacterStatus::CharacterStatus( int hp_max , int attack , int exp )
 : m_hp_max( hp_max )
 , m_hp( hp_max )
 , m_attack( attack )
 , m_exp( exp )
 , m_exp_max( s_default_exp_max )
 , m_is_guard( false )
 , m_attack_frame( 0 )
{
}

int CharacterStatus::AttackDamage() const
{
    return m_attack;
}


