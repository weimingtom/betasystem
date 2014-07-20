#include "UnitEnemy.hpp"
#include "Global.hpp"

void UnitEnemy::Update()
{
	UnitBase::Update();

	//追尾
	Vector2 move_vec = gUnitPlayer().GetPos() - mPos ;
	move_vec.Normalize();
	mPos += move_vec / 2;
	
	mDir = move_vec;
}

