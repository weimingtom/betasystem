#ifndef state_title_hpp
#define state_title_hpp

#include "System/StateBase.hpp"

/**
    �^�C�g����ʂ̑J��
*/
class StateTitle : public StateBase
{
public:
    StateTitle();
    ~StateTitle(){}
public:
    void Update();
    void Draw();
};

#endif
