#include "Project/Character.hpp"

namespace{

//ê¨í∑ó¶.
static float const s_glow_rate = 1.2f;
static int const s_exp_max = 100;

}//namespace unnamed

Character::Character( int hp_max , int attack , int exp )
 : m_level( 1 )
 , m_hp_max( hp_max )
 , m_hp( hp_max )
 , m_attack( attack )
 , m_exp( exp )
{
}

void Character::UpLevel()
{
    m_hp_max = static_cast<int>( m_hp_max * s_glow_rate );
    m_attack = static_cast<int>( m_attack * s_glow_rate );
}

void Character::SetLevel( int level )
{
    for( int i = m_level ; i < level ; i ++ )
    {
        UpLevel();
    }
}

bool Character::CanUpLevel() const
{
    return ( s_exp_max <= m_exp );
}

