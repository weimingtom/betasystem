#include "InputKey.hpp"

#include <DxLib.h>

class InputKey::Impl : public InputKey
{
public:
    Impl(){}
    ~Impl(){}
    
public:
    void Update();
    bool IsTrig( InputKey::Type ) const;
    bool IsHold( InputKey::Type ) const;
    
private:
    static int const m_key_flag[ InputKey::Type_Num ];
    int m_press_frame[ InputKey::Type_Num ];
};

int const InputKey::Impl::m_key_flag[ InputKey::Type_Num ] =
{
    KEY_INPUT_UP,
    KEY_INPUT_LEFT,
    KEY_INPUT_RIGHT,
    KEY_INPUT_DOWN,
    KEY_INPUT_BACK,
    KEY_INPUT_RETURN,
    KEY_INPUT_RSHIFT,
    KEY_INPUT_LCONTROL,
    KEY_INPUT_RCONTROL,
    KEY_INPUT_0,
    KEY_INPUT_1,
    KEY_INPUT_2,
    KEY_INPUT_3,
    KEY_INPUT_4,
    KEY_INPUT_5,
    KEY_INPUT_6,
    KEY_INPUT_7,
    KEY_INPUT_8,
    KEY_INPUT_9,
    KEY_INPUT_F1,
    KEY_INPUT_F2,
    KEY_INPUT_F3,
    KEY_INPUT_F4,
    KEY_INPUT_F5,
    KEY_INPUT_F6,
    KEY_INPUT_F7,
    KEY_INPUT_F8,
    KEY_INPUT_F9,
    KEY_INPUT_F10,
    KEY_INPUT_F11,
    KEY_INPUT_F12,
};

void InputKey::Impl::Update()
{
    for( int i = 0 ; i < InputKey::Type_Num ; i++ )
    {
        if( CheckHitKey( m_key_flag[i] ) == 1 )
        {
            m_press_frame[i]++;
        }else{
            m_press_frame[i] = 0;
        }
    }
}

bool InputKey::Impl::IsTrig( InputKey::Type type ) const
{
    return ( m_press_frame[type] == 1 );
}

bool InputKey::Impl::IsHold( InputKey::Type type ) const
{
    return ( m_press_frame[type] != 0 );
}

InputKey* new_InputKey()
{
    return new InputKey::Impl();
}

