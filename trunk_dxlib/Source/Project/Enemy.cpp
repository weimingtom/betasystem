#include "Project/Enemy.hpp"

#include "Project/Draw.hpp"

Enemy::Enemy()
 : m_pos( Vector2(0,0) )
 , m_speed( Vector2(0,0) )
 , m_is_alive( true )
{
}

void Enemy::Update()
{
	m_pos += m_speed;
}

void Enemy::Draw( Vector2 camera_pos ) const
{
    Vector2 hoge = m_pos - camera_pos;
	DrawTexture( hoge , ImageType_Enemy );
}

