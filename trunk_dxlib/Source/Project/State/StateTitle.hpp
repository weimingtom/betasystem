#ifndef state_title_hpp
#define state_title_hpp

class StateManagerBase;
#include "System/StateBase.hpp"

/**
    ƒ^ƒCƒgƒ‹‰æ–Ê‚Ì‘JˆÚ
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
    enum Step
    {
        Step_Title,
        Step_TitleMovie,
    };
private:
    StateManagerBase* m_manager;
    Step m_step;
    int m_frame;
};

#endif
