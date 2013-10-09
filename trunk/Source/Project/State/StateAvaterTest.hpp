#ifndef state_AvaterTest_hpp
#define state_AvaterTest_hpp

#include "System/StateBase.hpp"


class StateAvaterTest : public StateBase
{
public:
    StateAvaterTest();
    ~StateAvaterTest();
public:
	void Update();
	void Draw() const;
};

#endif
