#ifndef include_guard_015785ff_7b6d_4918_b984_a513a28fc9f1
#define include_guard_015785ff_7b6d_4918_b984_a513a28fc9f1

class Vector2
{
public:
    Vector2()
    : x(0)
    , y(0)
    {
    }
    Vector2( double x_ , double y_ )
    {
        x = x_;
        y = y_;
    }
    
    Vector2 operator +( Vector2 const& vec2 ) const
    {
        Vector2 result;
        result.x = this->x + vec2.x;
        result.y = this->y + vec2.y;
        return result;
    }
    Vector2 operator -( Vector2 const& vec2 ) const
    {
        Vector2 result;
        result.x = this->x - vec2.x;
        result.y = this->y - vec2.y;
        return result;
    }
    Vector2 operator +=( Vector2 const& vec2 )
    {
        this->x += vec2.x;
        this->y += vec2.y;
		return *this;
    }

public:
    double x;
    double y;
};

#endif

