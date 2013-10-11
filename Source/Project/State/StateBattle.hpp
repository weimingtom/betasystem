#ifndef STATE_BATTLE_HPP__
#define STATE_BATTLE_HPP__

#include "System/StateBase.hpp"

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
};

#endif // STATE_BATTLE_HPP__
