#include "Project/Enemy.hpp"

#include "Project/Draw.hpp"
#include "Project/AnimData.hpp"
#include "DxLibWrapper/AnimTexture.hpp"

Enemy::Enemy( Type type )
 : m_pos( Vector2(0,0) )
 , m_speed( Vector2(0,0) )
 , m_is_alive( true )
{
    ImageType image_type;
    switch( type ){
    case Type_GreenSlime:
        image_type = ImageType_GreenSlime;
        break;
    case Type_RedSlime:
        image_type = ImageType_RedSlime;
        break;
    case Type_SteelSlime:
        image_type = ImageType_SteelSlime;
        break;
    }
    
    m_anim_tex.reset( new AnimTexture(
        ImageHandleOf( image_type ), AnimDataOf( AnimType_EnemyIdling ) ) );
    m_hp = type + 1;
    m_exp = type + 5;
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
