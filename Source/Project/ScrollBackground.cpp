#include "ScrollBackground.hpp"

#include "Project/Draw.hpp"

namespace {

	static int const first_base = 0;
	static int const second_base = -640;

	/**
		スクロール後の描画開始位置を返す関数.
		@param scroll_x スクロールした値.
		@param base_x 基本座標.
	*/
	int ScrolledPosition( Vector2 scroll, int base_x )
	{
	    int position_x = static_cast<int>( base_x - scroll.x );
	    while( position_x < -640 ){
	        position_x += 1280;
	    }
		return position_x;
	}

} // namespace unnamed

ScrollBackground::ScrollBackground()
 : m_first( Vector2( first_base , 0 ) )
 , m_second( Vector2( second_base , 0 ) )
{
}

ScrollBackground::~ScrollBackground()
{
}

void ScrollBackground::SetScroll( Vector2 scroll )
{
	m_first.x = ScrolledPosition( scroll , first_base );
	m_second.x = ScrolledPosition( scroll , second_base );
}

void ScrollBackground::Draw( Vector2 camera_pos )
{
	DrawTexture( Vector2( m_first.x , m_first.y - camera_pos.y ) , ImageType_Forest );
	DrawTexture( Vector2( m_second.x , m_second.y - camera_pos.y ) , ImageType_Forest );
}

