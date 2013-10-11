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
    int mIndex;
};

#endif // STATE_BATTLE_HPP__
