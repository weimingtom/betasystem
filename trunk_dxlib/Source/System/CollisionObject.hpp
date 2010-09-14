#ifndef include_42fd8be4_7262_4a1d_a898_48ae6222af0c
#define include_42fd8be4_7262_4a1d_a898_48ae6222af0c

#include "System/CheckHit.hpp"
#include "System/Vector2.hpp"
#include "DxLibWrapper/Color.hpp"

class CollisionObject
{
public:
    CollisionObject( Vector2 pos , Vector2 size )
     : m_pos( pos )
     , m_size( size )
    {
    }
    virtual ~CollisionObject(){}
public:
    bool CheckHit( Vector2 pos ) const
    {
        return CheckHitRect( pos , m_pos , m_size );
    }
    
    void DrawCollision() const
    {
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
    
protected:
    Vector2 m_pos;
    Vector2 m_size;
};

#endif

