#ifndef state_test_msg_hpp
#define state_test_msg_hpp

class StateManagerBase;
#include <memory>
#include "System/StateBase.hpp"
#include "Project/Msg/MsgPrinter.hpp"
#include "Project/CharacterDrawer/CharacterDrawer.hpp"

/**
    メッセージテスト.
*/
class StateTestMsg : public StateBase
{
public:
    StateTestMsg( StateManagerBase* manager );
    ~StateTestMsg(){}
public:
	void Update();
	void Draw() const;
private:
    enum Step
    {
        Step_Default,
    };
private:
    StateManagerBase* m_manager;
    Step m_step;
    std::auto_ptr<MsgPrinter> m_msg_printer;
    std::auto_ptr<CharacterDrawer> m_chara_drawer;
};

#endif

