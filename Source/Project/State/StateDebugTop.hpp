#ifndef STATE_DEBUG_TOP__
#define STATE_DEBUG_TOP__

#include "System/StateBase.hpp"

namespace Princess{

class StateDebugTop : public StateBase
{
public:
    StateDebugTop();
    ~StateDebugTop(){}
public:
    void Update();
    void Draw();
private:
    int mIndex;
};

} // namespace Princess

#endif
