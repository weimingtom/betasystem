#ifndef scroll_background_hpp
#define scroll_background_hpp

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
    void SetScroll( int scroll_x );
    void Draw();

private:
    int m_first_x;	//!< �P���ڂ̔w�i�̍��W.
	int m_second_x;	//!< �Q���ڂ̔w�i�̍��W.
};



#endif //scroll_background_hpp
