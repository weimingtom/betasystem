#ifndef include_c5b4571e_b687_429b_aa72_b7a2a9dd5334
#define include_c5b4571e_b687_429b_aa72_b7a2a9dd5334

#include "System/Vector2.hpp"

class Button
{
public:
    friend Button* new_Button( int image_handle , Vector2 pos , Vector2 size );
    virtual ~Button(){}
    
public:
    virtual Vector2 Position() const = 0;
    virtual Vector2 Size() const = 0;
    virtual void Draw() const = 0;
    virtual bool CheckHit( Vector2 pos ) const = 0;
    
private:
    class Impl;
};

Button* new_Button( int image_handle , Vector2 pos , Vector2 size );

#endif

