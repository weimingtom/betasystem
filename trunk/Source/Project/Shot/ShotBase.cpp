#include "ShotBase.hpp"


static ShotManager sShotManager;

ShotManager& gShotManager()
{
	return sShotManager;
}

