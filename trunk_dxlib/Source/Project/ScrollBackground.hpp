#ifndef scroll_background_hpp
#define scroll_background_hpp

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
    void SetScroll( int scroll_x );
    void Draw();

private:
    int m_first_x;	//!< １枚目の背景の座標.
	int m_second_x;	//!< ２枚目の背景の座標.
};



#endif //scroll_background_hpp
