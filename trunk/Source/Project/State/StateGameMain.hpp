#ifndef STATE_GAME_MAIN__
#define STATE_GAME_MAIN__

#include "System/StateBase.hpp"
#include "DxLibWrapper/LogPrinter.hpp"
#include "Project/PlayerStatus.h"

class StateGameMain : public StateBase
{
public:
    StateGameMain();
    ~StateGameMain(){}
public:
    void Update();
    void Draw() const;
private:
    PlayerStatus mPlayerStatus;
};

#endif // STATE_GAME_MAIN__

