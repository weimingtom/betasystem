#include "Project/Enemy.hpp"

#include "Project/Draw.hpp"
#include "Project/AnimData.hpp"
#include "DxLibWrapper/AnimTexture.hpp"
#include "System/Range.hpp"

Enemy::Enemy( Type type )
 : m_pos( Vector2(0,0) )
 , m_speed( Vector2(0,0) )
 , m_is_alive( true )
 , m_is_visible( true )
 , m_frame(0)
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
    m_exp = (type + 1) * 2;
}

void Enemy::Update()
{
	m_pos += m_speed;
	m_anim_tex->Update();
	m_anim_tex->Set(m_pos);
	int const count_max = 100;
	if( !m_is_alive ){
	    m_frame++;
	    m_frame = Clamp( 0, m_frame, count_max );
	    if(m_frame == count_max){
	        m_is_visible = false;
	    }
	}
}

void Enemy::Draw( Vector2 camera_pos ) const
{
    if( m_is_visible ){
        m_anim_tex->Draw( camera_pos );
    }
}

void Enemy::SetPosition( Vector2 pos )
{
	m_pos = pos;
}
