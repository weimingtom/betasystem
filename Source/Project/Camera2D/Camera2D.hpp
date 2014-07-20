#ifndef Camera2D_hpp_
#define Camera2D_hpp_

#include "System/Vector2.hpp"

//! 2Dカメラ.
class Camera2D
{
public:
	Camera2D(){}
	~Camera2D(){}
public:
	void Update();
	Vector2 GetDrawOffset(){ return Vector2( 320 - mPos.x, 240 - mPos.y ); }
	void SetLookAt( Vector2 pos ){ mPos = pos; }
private:
	Vector2 mPos;
};

Camera2D& gCamera2D();

#endif

