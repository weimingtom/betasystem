#include "DxLibWrapper/Button.hpp"

#include <memory>
#include "DxLibWrapper/DxLibWrapper.hpp"
#include "System/CheckHit.hpp"

class Button::Impl : public Button
{
public:
    Impl(
        int image_handle ,
        Vector2 pos ,
        Vector2 size ,
        ProcessBase* process );
    ~Impl();
    
public:
    void Draw() const;
    bool CheckHit( Vector2 pos ) const;
    void Process();
    
private:
    int const m_image_handle;
    Vector2 const m_pos;
    Vector2 const m_size;
    std::auto_ptr< ProcessBase > m_process;
};

Button::Impl::Impl(
    int image_handle ,
    Vector2 pos ,
    Vector2 size ,
    ProcessBase* process )
 : m_image_handle( image_handle )
 , m_pos( pos )
 , m_size( size )
 , m_process( process )
{
}

Button::Impl::~Impl()
{
}

void Button::Impl::Draw() const
{
    DrawGraph( m_pos , m_image_handle );
    //! @todo 当たり判定のデバッグ表示.
#ifndef NDEBUG
    DrawBox(
        m_pos.x ,
        m_pos.y ,
        m_pos.x + m_size.x ,
        m_pos.y + m_size.y ,
        ColorOf() ,
        FALSE );
#endif
}

bool Button::Impl::CheckHit( Vector2 pos ) const
{
    return CheckHitRect( pos , m_pos , m_size );
}

void Button::Impl::Process()
{
    m_process->Run();
}

Button* new_Button( int image_handle , Vector2 pos , Vector2 size , ProcessBase* process )
{
    return new Button::Impl( image_handle  , pos , size , process );
}

