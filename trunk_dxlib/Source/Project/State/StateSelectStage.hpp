#ifndef StateSelectStage_hpp
#define StateSelectStage_hpp

class StateManagerBase;
#include "System/StateBase.hpp"
#include "DxLibWrapper/Button.hpp"

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
    std::string GetButtonName() const;
    void LevelUp();
private:
    StateManagerBase* m_manager;
    int m_frame;
    ButtonPtrList m_button_list;
};

#endif
