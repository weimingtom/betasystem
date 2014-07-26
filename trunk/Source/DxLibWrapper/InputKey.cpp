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
    bool IsRelease( InputKey::Type ) const;
    int GetHoldFrame( Type type ) const;
    
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
	KEY_INPUT_A,
	KEY_INPUT_B,
	KEY_INPUT_C,
	KEY_INPUT_D,
	KEY_INPUT_E,
	KEY_INPUT_F,
	KEY_INPUT_G,
	KEY_INPUT_H,
	KEY_INPUT_I,
	KEY_INPUT_J,
	KEY_INPUT_K,
	KEY_INPUT_L,
	KEY_INPUT_M,
	KEY_INPUT_N,
	KEY_INPUT_O,
	KEY_INPUT_P,
	KEY_INPUT_Q,
	KEY_INPUT_R,
	KEY_INPUT_S,
	KEY_INPUT_T,
	KEY_INPUT_U,
	KEY_INPUT_V,
	KEY_INPUT_W,
	KEY_INPUT_X,
	KEY_INPUT_Y,
	KEY_INPUT_Z,
};

void InputKey::Impl::Update()
{
    for( int i = 0 ; i < InputKey::Type_Num ; i++ )
    {
    	if( m_press_frame[i] == -1 ){
    		m_press_frame[i] = 0;
    	}
    }

    for( int i = 0 ; i < InputKey::Type_Num ; i++ )
    {
        if( CheckHitKey( m_key_flag[i] ) == 1 )
        {
            m_press_frame[i]++;
        }else{
            m_press_frame[i] = -1;
        }
    }
}

bool InputKey::Impl::IsTrig( InputKey::Type type ) const
{
    return ( m_press_frame[type] == 1 );
}

bool InputKey::Impl::IsHold( InputKey::Type type ) const
{
    return ( m_press_frame[type] > 0 );
}

bool InputKey::Impl::IsRelease( InputKey::Type type ) const
{
    return ( m_press_frame[type] == -1 );
}

int InputKey::Impl::GetHoldFrame( InputKey::Type type ) const
{
    return m_press_frame[type];
}

InputKey* new_InputKey()
{
    return new InputKey::Impl();
}

