#include "KeyboardInput.hpp"

#include "DxLibWrapper/ReturnVariable.hpp"

class KeyboardInput::Impl : public KeyboardInput
{
public:
    Impl();
    ~Impl();
    
public:
    void Update();
    bool IsTrig( KeyboardInput::Type ) const;
    bool IsHold( KeyboardInput::Type ) const;
    
private:
    static int const m_key_flag[ KeyboardInput::Type_Num ];
    int m_press_frame[ KeyboardInput::Type_Num ];
};

int const KeyboardInput::Impl::m_key_flag[ KeyboardInput::Type_Num ] =
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

KeyboardInput::Impl::Impl()
{
}

KeyboardInput::Impl::~Impl()
{
}

void KeyboardInput::Impl::Update()
{
    for( int i = 0 ; i < KeyboardInput::Type_Num ; i++ )
    {
        if( CheckHitKey( m_key_flag[i] ) == 1 )
        {
            m_press_frame[i]++;
        }else{
            m_press_frame[i] = 0;
        }
    }
}

bool KeyboardInput::Impl::IsTrig( KeyboardInput::Type type ) const
{
    return ( m_press_frame[type] == 1 );
}

bool KeyboardInput::Impl::IsHold( KeyboardInput::Type type ) const
{
    return ( m_press_frame[type] != 0 );
}

KeyboardInput* new_KeyboardInput()
{
    return new KeyboardInput::Impl();
}

