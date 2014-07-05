#ifndef state_title_hpp
#define state_title_hpp

#include "System/StateBase.hpp"

/**
*/
class StateCharacterGenerate : public StateBase
{
public:
    StateCharacterGenerate();
    ~StateCharacterGenerate(){}
public:
	void Update();
	void Draw();
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
