#include "DxLibWrapper/Button.hpp"

#include <memory>
#include "DxLib.h"
#include "DxLibWrapper/Graphics.hpp"
#include "DxLibWrapper/Color.hpp"
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
    DrawGraph( m_pos , m_image_handle );
    //! @todo 当たり判定のデバッグ表示.
#ifndef NDEBUG
    DrawBox(
        static_cast<int>( m_pos.x ),
        static_cast<int>( m_pos.y ),
        static_cast<int>( m_pos.x + m_size.x ),
        static_cast<int>( m_pos.y + m_size.y ),
        ColorOf( 255 , 0 , 0 ) ,
        FALSE );
#endif
}

