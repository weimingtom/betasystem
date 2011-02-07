#include "ScrollBackground.hpp"

#include "Project/Draw.hpp"

namespace {

	static int const first_base = 0;
	static int const second_base = 640;

	/**
		�X�N���[����̕`��J�n�ʒu��Ԃ��֐�.
		@param scroll_x �X�N���[�������l.
		@param base_x ��{���W.
	*/
	int ScrolledPosition( int scroll_x, int base_x )
	{
	    int position_x = base_x - scroll_x;
	    while( position_x < -640 ){
	        position_x += 1280;
	    }
		return position_x;
	}

} // namespace unnamed

ScrollBackground::ScrollBackground()
 : m_first_x( first_base )
 , m_second_x( second_base )
{
}

ScrollBackground::~ScrollBackground()
{
}

void ScrollBackground::SetScroll( int scroll_x )
{
    int const first_base = 0;
	
	m_first_x = ScrolledPosition( scroll_x, first_base );
	m_second_x = ScrolledPosition( scroll_x, second_base );
}

void ScrollBackground::Draw()
{
	DrawTexture( m_first_x, 0, ImageType_Forest );
	DrawTexture( m_second_x, 0, ImageType_Forest );
}

