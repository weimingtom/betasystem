#ifndef StateSelectStage_hpp
#define StateSelectStage_hpp

class StateManagerBase;
#include "System/StateBase.hpp"

/**
    �^�C�g����ʂ̑J��
*/
class StateSelectStage : public StateBase
{
public:
    StateSelectStage( StateManagerBase* manager );
    ~StateSelectStage(){}
public:
	void Update();
	void Draw() const;
private:
    StateManagerBase* m_manager;
    int m_frame;
};

#endif
