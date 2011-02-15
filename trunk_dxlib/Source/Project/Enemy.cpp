#include "Project/Enemy.hpp"

Enemy::Enemy( Vector2 init_pos )
 : m_pos( init_pos )
 , m_speed( Vector2(0,0) )
 , m_is_alive( true )
{
}

void Enemy::Update()
{
	m_pos += m_speed;
}

void Enemy::Draw() const
{
}

