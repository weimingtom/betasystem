#ifndef state_test_msg_hpp
#define state_test_msg_hpp

class StateManagerBase;
#include "System/StateBase.hpp"

/**
    ���b�Z�[�W�e�X�g.
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
    int m_frame;
};

#endif

