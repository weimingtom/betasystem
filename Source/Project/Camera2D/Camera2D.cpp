#include "Camera2D.hpp"

#include "Project/Unit/UnitPlayer.hpp"

void Camera2D::Update()
{
//	SetLookAt( gUnitPlayer().GetPos() );
}

Camera2D& gCamera2D()
{
	static Camera2D sCamera2D;
	return sCamera2D;
}

