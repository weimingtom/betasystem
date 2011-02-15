#ifndef scroll_background_hpp
#define scroll_background_hpp

#include "System/Vector2.hpp"

/**
	スクロールする背景を実現するクラス.
*/
class ScrollBackground
{
public:
    ScrollBackground();
    ~ScrollBackground();

public:
    /**
        背景をずらす量を設定する.
    */
    void SetScroll( Vector2 pos );
	void Draw( Vector2 camera_pos );

private:
    Vector2 m_first;	//!< １枚目の背景の座標.
	Vector2 m_second;	//!< ２枚目の背景の座標.
};



#endif //scroll_background_hpp
