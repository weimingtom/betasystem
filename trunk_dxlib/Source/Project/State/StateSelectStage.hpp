#ifndef StateSelectStage_hpp
#define StateSelectStage_hpp

class StateManagerBase;
#include "System/StateBase.hpp"

/**
    ƒ^ƒCƒgƒ‹‰æ–Ê‚Ì‘JˆÚ
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
