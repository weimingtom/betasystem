#include "Project/Character.hpp"
#include "DxLibWrapper/Random.hpp"

namespace{

//ê¨í∑ó¶.
static float const s_glow_rate = 1.5f;
static int const s_exp_max = 100;
static int const s_default_action_point = 3;

}//namespace unnamed

Character::Character( int hp_max , int attack , int exp )
 : m_level( 1 )
 , m_hp_max( hp_max )
 , m_hp( hp_max )
 , m_attack( attack )
 , m_exp( exp )
 , m_action_point( s_default_action_point )
 , m_action_point_max( s_default_action_point )
{
    for( int i = 0 ; i < AttackType_Num ; i++ )
    {
        m_attack_list[i] = static_cast< AttackType >( i );
    }
    m_select_index = 0 ;
}

void Character::UpLevel()
{
    m_hp_max = static_cast<int>( m_hp_max * s_glow_rate );
    m_attack = static_cast<int>( m_attack * s_glow_rate );
    m_level++;
    m_exp -= s_exp_max;
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

bool Character::IsLive() const
{
    return ( m_hp > 0 );
}

AttackType Character::AttackTypeOf( int index ) const
{
    return m_attack_list[ index ];
}

int Character::AttackDamage() const
{
    float const rand = static_cast<float>( GetRandToMax( 4 ) );
    float keisuu = ( rand - 2 ) / 10 ;
    
    return static_cast<int>( m_attack + m_attack * keisuu );
}


