﻿#ifndef STATE_DEBUG_TOP__
#define STATE_DEBUG_TOP__

#include "System/StateBase.hpp"

class StateDebugTop : public StateBase
{
public:
    StateDebugTop();
    ~StateDebugTop(){}
public:
    void Update();
    void Draw() const;
private:
    int mIndex;
};

#endif
