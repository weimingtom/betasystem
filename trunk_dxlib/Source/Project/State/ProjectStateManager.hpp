#ifndef include_4043f656_29d2_4fa5_b7b8_641d2d447994
#define include_4043f656_29d2_4fa5_b7b8_641d2d447994

class StateManagerBase;

/**
    �v���W�F�N�g�̑�{�̑J��.
*/
enum ProjectState
{
    ProjectState_Title,
    ProjectState_SelectStage,
    ProjectState_Battle,
    ProjectState_GameOver,
    ProjectState_TestMsg,
    
    ProjectState_DebugTop,
    ProjectState_Num,
};

StateManagerBase* new_ProjectStateManager();

#endif

