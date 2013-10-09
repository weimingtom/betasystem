#ifndef STATE_EQUIP_TEST_HPP__
#define STATE_EQUIP_TEST_HPP__

#include "System/StateBase.hpp"

class StateEquipTest : public StateBase
{
public:
    StateEquipTest();
    ~StateEquipTest();
public:
	void Update();
	void Draw() const;
};

#endif // STATE_EQUIP_TEST_HPP__
