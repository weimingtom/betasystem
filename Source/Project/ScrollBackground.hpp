#ifndef scroll_background_hpp
#define scroll_background_hpp

#include "System/Vector2.hpp"

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
    void SetScroll( Vector2 pos );
	void Draw( Vector2 camera_pos );

private:
    Vector2 m_first;	//!< ‚P–‡–Ú‚Ì”wŒi‚ÌÀ•W.
	Vector2 m_second;	//!< ‚Q–‡–Ú‚Ì”wŒi‚ÌÀ•W.
};



#endif //scroll_background_hpp
