#ifndef STATE_EQUIP_TEST_HPP__
#define STATE_EQUIP_TEST_HPP__

#include <memory>
#include "System/StateBase.hpp"
#include "Project/Avater/Avater.hpp"

class StateEquipTest : public StateBase
{
public:
    StateEquipTest();
    ~StateEquipTest();
public:
	void Update();
	void Draw() const;
private:
    int mIndex;
    std::auto_ptr<Avater> mAvater;
};

#endif // STATE_EQUIP_TEST_HPP__
