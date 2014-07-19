#ifndef include_guard_015785ff_7b6d_4918_b984_a513a28fc9f1
#define include_guard_015785ff_7b6d_4918_b984_a513a28fc9f1

#include <cmath> // sqrt

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
    Vector2 operator *( double mul )
    {
        Vector2 result;
        result.x = this->x * mul;
        result.y = this->y * mul;
		return result;
    }
    Vector2 operator /( double devide )
    {
        Vector2 result;
        result.x = this->x / devide;
        result.y = this->y / devide;
		return result;
    }
    Vector2 operator +=( Vector2 const& vec2 )
    {
        this->x += vec2.x;
        this->y += vec2.y;
		return *this;
    }
    Vector2 operator *=( double mul )
    {
        Vector2 result;
        this->x *= mul;
        this->y *= mul;
		return *this;
    }
    Vector2 operator /=( double devide )
    {
        Vector2 result;
        this->x /= devide;
        this->y /= devide;
		return *this;
    }
    
	double Length() const
    {
        return std::sqrt(x * x + y * y);
    }
    // ³‹K‰»(ƒxƒNƒgƒ‹‚Ì’·‚³‚ğ1‚É‚·‚é)
    Vector2 Normalize()
    {
    	if( Length() != 0.0f ){
	        double const mag = 1 / Length();
	        x *= mag;
	        y *= mag;
	    }
	    return *this;
    }

public:
    double x;
    double y;
};

#endif

