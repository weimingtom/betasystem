#include "KeyBoardInput.hpp"

class KeyBoardInput::Impl : public KeyBoardInput
{
public:
    Impl();
    ~Impl();
    
public:
    void Update();
    bool IsTrig() const;
    bool IsHold() const;
    
private:
    static enum const m_key_flag[ KeyBoardInput::Type_Num ]
    int m_press_frame[ KeyBoardInput::Type_Num ];
};

enum const m_key_flag[ KeyBoardInput::Type_Num ] =
{
    KEY_INPUT_UP,
    KEY_INPUT_LEFT,
    KEY_INPUT_RIGHT,
    KEY_INPUT_DOWN,
    KEY_INPUT_BACK,
    KEY_INPUT_RETURN,
    KEY_INPUT_RSHIFT,
    KEY_INPUT_RCONTROL,
};

KeyBoardInput::Impl::Impl()
{
}

KeyBoardInput::Impl::~Impl()
{
}

KeyBoardInput::Impl::Update()
{
    for( int i = 0 ; i < KeyBoardInput::Type_Num ; i++ )
    {
        if( CheckHitKey( m_key_flag[i] ) == 1 )
        {
            m_press_frame[i]++;
        }else{
            m_press_frame[i] = 0;
        }
    }
}

KeyBoardInput::Impl::IsTrig( KeyBoardInput::Type type ) const
{
    return ( m_press_frame[type] == 1 );
}

KeyBoardInput::Impl::IsHold( KeyBoardInput::Type type ) const
{
    return ( m_press_frame[type] != 0 );
}

