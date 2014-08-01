#ifndef _StateActionGame_
#define _StateActionGame_

#include "System/StateBase.hpp"
#include "DxLibWrapper/Random.hpp"
#include "Project/Unit/UnitEnemy.hpp"

//! アクションゲームシーン.
class StateActionGame : public StateBase
{
public:
    StateActionGame();
    ~StateActionGame(){}
public:
	void Update();
	void Draw();
private:
	static int const kEnemyMax = 16;
	static int const kShotMax = 32;
	static int const kMapChipMax = 32;
private:
	void InitEnemy();
private:
    UnitEnemy mEnemy[kEnemyMax];
    int mStageFrame;
    int mPreHoldFrame;
    int mWalkFrame;
    int mMapChip[kMapChipMax][kMapChipMax];
    int mFrame;
};

#endif
