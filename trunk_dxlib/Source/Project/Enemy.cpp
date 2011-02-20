#include "Project/Enemy.hpp"

#include "Project/Draw.hpp"
#include "Project/AnimData.hpp"
#include "DxLibWrapper/AnimTexture.hpp"

Enemy::Enemy()
 : m_pos( Vector2(0,0) )
 , m_speed( Vector2(0,0) )
 , m_is_alive( true )
 , m_anim_tex( new AnimTexture(
    ImageHandleOf( ImageType_Enemy ), AnimDataOf( AnimType_EnemyIdling ) ) )
{
}

void Enemy::Update()
{
	m_pos += m_speed;
	m_anim_tex->Update();
	m_anim_tex->Set(m_pos);
}

void Enemy::Draw( Vector2 camera_pos ) const
{
    m_anim_tex->Draw( camera_pos );
}

void Enemy::SetPosition( Vector2 pos )
{
	m_pos = pos;
}
