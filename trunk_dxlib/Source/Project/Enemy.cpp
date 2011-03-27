#include "Project/Enemy.hpp"

#include "Project/Draw.hpp"
#include "Project/AnimData.hpp"
#include "DxLibWrapper/AnimTexture.hpp"

Enemy::Enemy( Type type )
 : m_pos( Vector2(0,0) )
 , m_speed( Vector2(0,0) )
 , m_is_alive( true )
{
    ImageType const image_type = (type==Type_GreenSlime) ? ImageType_GreenSlime : ImageType_RedSlime;
    m_anim_tex.reset( new AnimTexture(
        ImageHandleOf( image_type ), AnimDataOf( AnimType_EnemyIdling ) ) );
    m_hp = type + 1;
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
