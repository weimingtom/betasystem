#include "Project/Enemy.hpp"

#include "Project/Draw.hpp"
#include "Project/AnimData.hpp"
#include "DxLibWrapper/AnimTexture.hpp"
#include "System/Range.hpp"

Enemy::Enemy( Type type )
 : m_pos( Vector2(0,0) )
{
    ImageType image_type;
    switch( type ){
    case Type_GreenSlime:
        image_type = ImageType_GreenSlime;
		m_hp = 10;
        m_exp = 1;
        break;
    case Type_RedSlime:
		m_hp = 20;
        image_type = ImageType_RedSlime;
        m_exp = 2;
        break;
    case Type_SteelSlime:
		m_hp = 30;
        image_type = ImageType_SteelSlime;
        m_exp = 3;
        break;
    }
	m_speed = 1;
	m_attack = 10;

    
    m_anim_tex.reset( new AnimTexture(
        ImageHandleOf( image_type ), AnimDataOf( AnimType_EnemyIdling ) ) );
}

void Enemy::Update()
{
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
