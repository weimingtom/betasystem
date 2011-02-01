#ifndef include_4043f656_29d2_4fa5_b7b8_641d2d447994
#define include_4043f656_29d2_4fa5_b7b8_641d2d447994

class StateManagerBase;

enum ProjectState
{
    ProjectState_Battle,
    ProjectState_GameOver,
};

StateManagerBase* new_ProjectStateManager();

#endif

