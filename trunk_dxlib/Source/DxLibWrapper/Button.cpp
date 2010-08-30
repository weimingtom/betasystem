#include "DxLibWrapper/Button.hpp"

#include <memory>
#include "DxLib.h"
#include "DxLibWrapper/Graphics.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/CheckHit.hpp"

class Button::Impl : public Button
{
public:
    Impl(
        int image_handle ,
        Vector2 pos ,
        Vector2 size ,
        ProcessBase* process ,
        std::string name );
    ~Impl();
    
public:
    void Draw() const;
    bool CheckHit( Vector2 pos ) const;
    bool CanProcess() const;
    bool HasProcess() const;
    void Process();
    std::string Name() const;
    
private:
    int const m_image_handle;
    Vector2 const m_pos;
    Vector2 const m_size;
    std::auto_ptr< ProcessBase > m_process;
    std::string const m_name;
};

Button::Impl::Impl(
    int image_handle ,
    Vector2 pos ,
    Vector2 size ,
    ProcessBase* process ,
    std::string name )
 : m_image_handle( image_handle )
 , m_pos( pos )
 , m_size( size )
 , m_process( process )
 , m_name( name )
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
        static_cast<int>( m_pos.x ),
        static_cast<int>( m_pos.y ),
        static_cast<int>( m_pos.x + m_size.x ),
        static_cast<int>( m_pos.y + m_size.y ),
        ColorOf( 255 , 0 , 0 ) ,
        FALSE );
#endif
}

bool Button::Impl::CheckHit( Vector2 pos ) const
{
    return CheckHitRect( pos , m_pos , m_size );
}

bool Button::Impl::HasProcess() const
{
    return ( m_process.get() != 0 );
}

bool Button::Impl::CanProcess() const
{
    return m_process->CanRunning();
}

void Button::Impl::Process()
{
    m_process->Run();
}

std::string Button::Impl::Name() const
{
    return m_name;
}

Button* new_Button( int image_handle , Vector2 pos , Vector2 size , ProcessBase* process , std::string name )
{
    return new Button::Impl( image_handle  , pos , size , process , name );
}

