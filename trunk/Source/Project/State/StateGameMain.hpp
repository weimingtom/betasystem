#ifndef STATE_GAME_MAIN__
#define STATE_GAME_MAIN__

#include "System/StateBase.hpp"

class StateGameMain : public StateBase
{
public:
    StateGameMain();
    ~StateGameMain(){}
public:
    void Update();
    void Draw() const;
};

#endif // STATE_GAME_MAIN__

