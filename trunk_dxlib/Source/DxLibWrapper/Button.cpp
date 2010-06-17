#include "DxLibWrapper/Button.hpp"

#include "DxLibWrapper/DxLibWrapper.hpp"
#include "System/CheckHit.hpp"

class Button::Impl : public Button
{
public:
    Impl( int image_handle , Vector2 pos , Vector2 size );
    ~Impl();
    
public:
    Vector2 Position() const;
    Vector2 Size() const;
    void Draw() const;
    bool CheckHit( Vector2 pos ) const;

private:
    int const m_image_handle;
    Vector2 const m_pos;
    Vector2 const m_size;
};

Button::Impl::Impl( int image_handle , Vector2 pos , Vector2 size )
 : m_image_handle( image_handle )
 , m_pos( pos )
 , m_size( size )
{
}

Button::Impl::~Impl()
{
}

bool Button::Impl::CheckHit( Vector2 pos ) const
{
    return CheckHitRect( pos , m_pos , m_size );
}

Vector2 Button::Impl::Position() const
{
    return m_pos;
}

Vector2 Button::Impl::Size() const
{
    return m_size;
}

void Button::Impl::Draw() const
{
    DrawGraph( m_pos , m_image_handle );
}

Button* new_Button( int image_handle , Vector2 pos , Vector2 size )
{
    return new Button::Impl( image_handle  , pos , size );
}

