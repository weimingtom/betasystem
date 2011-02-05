#ifndef state_title_hpp
#define state_title_hpp

class StateManagerBase;
#include "System/StateBase.hpp"

/**
    �^�C�g����ʂ̑J��
*/
class StateTitle : public StateBase
{
public:
    StateTitle( StateManagerBase* manager );
    ~StateTitle(){}
public:
    void Update();
    void Draw();
private:
    StateManagerBase* m_manager;
};

#endif
