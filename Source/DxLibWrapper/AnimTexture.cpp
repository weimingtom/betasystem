#include "AnimTexture.hpp"
#include <DxLib.h>

AnimTexture::AnimTexture( int image_handle, AnimFormat const& anim_data )
 : m_image_handle( image_handle )
 , m_pos( Vector2(0,0) )
{
    Set( anim_data );
}

void AnimTexture::Update()
{
    //フレームを進めて、達したらインデックスを進める.
    m_frame++;
    if( m_frame > m_anim_data.draw_frame ){
        m_frame=0;
        m_current_index++;
    }
    //インデックスが終了に達したら、ループを判断する.
    if( m_current_index >= m_anim_data.anim_num ){
        if( m_anim_data.loop_num == AnimFormat::InfinityLoop ){
            m_current_index = 0;
        }
        else if( m_remain_loop > 0 ){
            m_remain_loop--;
            m_current_index = 0;
        }
    }
}

void AnimTexture::Draw( Vector2 const& camera_pos ) const
{
    int const width = static_cast<int>(m_anim_data.width);
    int const height = static_cast<int>(m_anim_data.height);
    DrawRectGraph(
        static_cast<int>(m_pos.x - camera_pos.x),
        static_cast<int>(m_pos.y - camera_pos.y),
        m_anim_data.begin_x + width*m_current_index,
        m_anim_data.begin_y,
        m_anim_data.width,
        m_anim_data.height,
        m_image_handle, TRUE, FALSE );
}

void AnimTexture::Set( AnimFormat const& anim_data )
{
    m_current_index = 0;
    m_frame = 0;
    m_anim_data = anim_data;
    m_remain_loop = anim_data.loop_num;
}

