#include "ScrollBackground.hpp"

#include "Project/Draw.hpp"

ScrollBackground::ScrollBackground()
 : m_first_x(0)
{
}

ScrollBackground::~ScrollBackground()
{
}

void ScrollBackground::SetScroll( int scroll_x )
{
    int const first_base = 0;
    m_first_x = first_base - scroll_x;
    while( m_first_x < -640 ){
        m_first_x += 1280;
    }
}

void ScrollBackground::Draw()
{
	DrawTexture( m_first_x, 0, ImageType_Forest );
}

