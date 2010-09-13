#ifndef include_42fd8be4_7262_4a1d_a898_48ae6222af0c
#define include_42fd8be4_7262_4a1d_a898_48ae6222af0c

#include "System/CheckHit.hpp"
#include "System/Vector2.hpp"

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
    
protected:
    Vector2 m_pos;
    Vector2 m_size;
};



#endif

