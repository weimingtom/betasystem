#include "MouseInput.hpp"
/*
	マウス入力関連.
*/

#include "DxLibWrapper.hpp"

class MouseInput::Impl : public MouseInput
{
public:
	Impl( int is_visible_cursor );
	~Impl();

public:
	void Update();

public:
	int GetX() const { return m_x; }
	int GetY() const { return m_y; }
	void SetPos( int x , int y ) const;
    bool IsTrig( MouseInput::Type type ) const ;
    bool IsHold( MouseInput::Type type ) const ;

private:
    void UpdatePosition();
    void UpdateInput();
    
private:
	int m_x;
	int m_y;
    int m_press_frame[ MouseInput::Type_Num ];
};


MouseInput::Impl::Impl( int is_visible_cursor )
: m_x( 0 )
, m_y( 0 )
{
	if( SetMouseDispFlag( is_visible_cursor ) == FunctionFailure )
	{
		exit( ApplicationFailure );
	}
}

MouseInput::Impl::~Impl()
{
}

void MouseInput::Impl::Update()
{
    UpdatePosition();
    UpdateInput();
}

void MouseInput::Impl::UpdatePosition()
{
	if( GetMousePoint( &m_x , &m_y ) == FunctionFailure )
	{
		exit( ApplicationFailure );
	}
}

void MouseInput::Impl::UpdateInput()
{
    int const input_flag[ MouseInput::Type_Num ] =
    {
        MOUSE_INPUT_RIGHT,
        MOUSE_INPUT_LEFT,
        MOUSE_INPUT_MIDDLE,
    };
    
    for( int i = 0 ; i < MouseInput::Type_Num ; i++ )
    {
        if( ( GetMouseInput() & input_flag[i] ) == 0 )
        {
            m_press_frame[i] = 0;
        }else{
            m_press_frame[i] ++;
        }
    }
}

bool MouseInput::Impl::IsTrig( MouseInput::Type type ) const
{
    return ( m_press_frame[ type ] == 1 );
}

bool MouseInput::Impl::IsHold( MouseInput::Type type ) const
{
    return ( m_press_frame[ type ] != 0 );
}

void MouseInput::Impl::SetPos( int x , int y ) const
{
	if( SetMousePoint( x , y ) == FunctionFailure )
	{
		exit( ApplicationFailure );
	}
}

MouseInput* new_MouseInput( int is_visible_cursor )
{
	return new MouseInput::Impl( is_visible_cursor );
}

