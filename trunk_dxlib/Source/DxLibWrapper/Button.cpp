#include "DxLibWrapper/Button.hpp"

#include <memory>
#include "DxLib.h"
#include "System/CheckHit.hpp"

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
//    DrawTexture( m_pos , m_image_handle );
    DrawCollision();
}

