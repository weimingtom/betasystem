#ifndef scroll_background_hpp
#define scroll_background_hpp

/**
	ƒXƒNƒ[ƒ‹‚·‚é”wŒi‚ğÀŒ»‚·‚éƒNƒ‰ƒX.
*/
class ScrollBackground
{
public:
    ScrollBackground();
    ~ScrollBackground();

public:
    /**
        ”wŒi‚ğ‚¸‚ç‚·—Ê‚ğİ’è‚·‚é.
    */
    void SetScroll( int scroll_x );
    void Draw();

private:
    int m_first_x;	//!< ‚P–‡–Ú‚Ì”wŒi‚ÌÀ•W.
	int m_second_x;	//!< ‚Q–‡–Ú‚Ì”wŒi‚ÌÀ•W.
};



#endif //scroll_background_hpp
