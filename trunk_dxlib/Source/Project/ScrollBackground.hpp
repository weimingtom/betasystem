#ifndef scroll_background_hpp
#define scroll_background_hpp

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
    int m_first_x;
};



#endif //scroll_background_hpp
