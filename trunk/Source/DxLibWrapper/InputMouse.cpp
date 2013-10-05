#include "InputMouse.hpp"
/*
	マウス入力関連.
*/
#include "ReturnVariable.hpp"
#include "System/Vector2.hpp"

class InputMouse::Impl : public InputMouse
{
public:
	Impl( int is_visible_cursor );
	~Impl();

public:
	void Update();

public:
    Vector2 Position() const { return Vector2( m_x , m_y ); }
    void SetPos( int x , int y ) const;
    bool IsTrig( InputMouse::Type type ) const ;
    bool IsHold( InputMouse::Type type ) const ;

private:
    void UpdatePosition();
    void UpdateInput();
    
private:
	int m_x;
	int m_y;
    int m_press_frame[ InputMouse::Type_Num ];
};


InputMouse::Impl::Impl( int is_visible_cursor )
: m_x( 0 )
, m_y( 0 )
{
	if( SetMouseDispFlag( is_visible_cursor ) == FunctionFailure )
	{
		exit( ApplicationFailure );
	}
}

InputMouse::Impl::~Impl()
{
}

void InputMouse::Impl::Update()
{
    UpdatePosition();
    UpdateInput();
}

void InputMouse::Impl::UpdatePosition()
{
	if( GetMousePoint( &m_x , &m_y ) == FunctionFailure )
	{
		exit( ApplicationFailure );
	}
}

void InputMouse::Impl::UpdateInput()
{
    int const input_flag[ InputMouse::Type_Num ] =
    {
        MOUSE_INPUT_RIGHT,
        MOUSE_INPUT_LEFT,
        MOUSE_INPUT_MIDDLE,
    };
    
    for( int i = 0 ; i < InputMouse::Type_Num ; i++ )
    {
        if( ( GetMouseInput() & input_flag[i] ) == 0 )
        {
            m_press_frame[i] = 0;
        }else{
            m_press_frame[i] ++;
        }
    }
}

bool InputMouse::Impl::IsTrig( InputMouse::Type type ) const
{
    return ( m_press_frame[ type ] == 1 );
}

bool InputMouse::Impl::IsHold( InputMouse::Type type ) const
{
    return ( m_press_frame[ type ] != 0 );
}

void InputMouse::Impl::SetPos( int x , int y ) const
{
	if( SetMousePoint( x , y ) == FunctionFailure )
	{
		exit( ApplicationFailure );
	}
}

InputMouse* new_InputMouse( int is_visible_cursor )
{
	return new InputMouse::Impl( is_visible_cursor );
}

