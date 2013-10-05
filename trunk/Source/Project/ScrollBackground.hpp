#ifndef scroll_background_hpp
#define scroll_background_hpp

#include "System/Vector2.hpp"

/**
	�X�N���[������w�i����������N���X.
*/
class ScrollBackground
{
public:
    ScrollBackground();
    ~ScrollBackground();

public:
    /**
        �w�i�����炷�ʂ�ݒ肷��.
    */
    void SetScroll( Vector2 pos );
	void Draw( Vector2 camera_pos );

private:
    Vector2 m_first;	//!< �P���ڂ̔w�i�̍��W.
	Vector2 m_second;	//!< �Q���ڂ̔w�i�̍��W.
};



#endif //scroll_background_hpp
