#ifndef STATE_GAME_MAIN__
#define STATE_GAME_MAIN__

#include <memory>
#include <vector>
#include "System/StateBase.hpp"
#include "DxLibWrapper/LogPrinter.hpp"
#include "Project/PlayerStatus.h"
#include "Project/DrawingKoyaku.h"

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
    std::auto_ptr<LogPrinter> mLogPrinter;
    std::vector<KoyakuType> mKoyakuList;
    static int const kKoyakuListMax = 10;
};

#endif // STATE_GAME_MAIN__

