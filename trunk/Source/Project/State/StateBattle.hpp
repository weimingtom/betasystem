#ifndef STATE_BATTLE_HPP__
#define STATE_BATTLE_HPP__

#include <memory>
#include "System/StateBase.hpp"
#include "Project/Avater/Avater.hpp"

class StateBattle : public StateBase
{
public:
    StateBattle();
    ~StateBattle();
public:
	void Update();
	void Draw() const;
private:
    enum BattleAction{
        BattleAction_Attack,
        BattleAction_Pray,
        BattleAction_Away,
        BattleAction_Num,
    };
private:
    int mIndex;
    std::auto_ptr<Avater> mEnemyAvater;
};

#endif // STATE_BATTLE_HPP__
