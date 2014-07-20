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
	static int const kEnemyMax = 32;
private:
    UnitEnemy mEnemy[kEnemyMax];
    int mStageFrame;
};

#endif
