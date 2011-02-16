#ifndef state_title_hpp
#define state_title_hpp

class StateManagerBase;
#include "System/StateBase.hpp"

/**
    タイトル画面の遷移
*/
class StateTitle : public StateBase
{
public:
    StateTitle( StateManagerBase* manager );
    ~StateTitle(){}
public:
	void Update();
	void Draw() const;
private:
    StateManagerBase* m_manager;
};

#endif
