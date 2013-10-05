#ifndef state_title_hpp
#define state_title_hpp

#include "System/StateBase.hpp"

/**
    ƒ^ƒCƒgƒ‹‰æ–Ê‚Ì‘JˆÚ
*/
class StateTitle : public StateBase
{
public:
    StateTitle();
    ~StateTitle(){}
public:
	void Update();
	void Draw() const;
private:
    enum Step
    {
        Step_Title,
    };
private:
    Step m_step;
    int m_frame;
};

#endif
