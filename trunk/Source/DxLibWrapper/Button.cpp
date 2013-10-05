#include "DxLibWrapper/Button.hpp"

#include <memory>
#include "DxLib.h"
#include "System/CheckHit.hpp"
#include "Project/Draw.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

Button::Button(
    int image_handle ,
    Vector2 pos ,
    Vector2 size ,
    std::string name )
 : CollisionObject( pos , size )
 , m_image_handle( image_handle )
 , m_name( name )
{
}

void Button::Draw() const
{
    DrawRectGraph( static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
        0, 0, static_cast<int>(m_size.x), static_cast<int>(m_size.y),
        ImageHandleOf(static_cast<ImageType>(m_image_handle)), TRUE, FALSE);
//    DrawTexture( m_pos , static_cast<ImageType>(m_image_handle) );
    DrawCollision();
    DrawFormatString( (int)m_pos.x , (int)m_pos.y, ColorOf(0,255,0) , "%s", m_name.c_str() );
}

