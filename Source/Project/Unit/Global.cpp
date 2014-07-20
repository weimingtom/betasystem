#include "Project/Unit/UnitPlayer.hpp"


static bool gIsVisibleCollision = false;

bool IsVisibleCollision()
{
	return gIsVisibleCollision;
}

void SetVisibleCollision( bool is_visible )
{
	gIsVisibleCollision = is_visible;
}

static UnitPlayer sUnitPlayer;

UnitPlayer& gUnitPlayer()
{
	return sUnitPlayer;
}



