#include "Project/ProcessRunAway.hpp"

#include "System/StateManagerBase.hpp"
#include "System/ProcessBase.hpp"
#include "Project/ProjectStateManager.hpp"


class ProcessRunAway : public ProcessBase
{
public:
    ProcessRunAway( StateManagerBase& project_state_manager );
public:
    void Run();
private:
    StateManagerBase& m_project_state_manager;
};

ProcessRunAway::ProcessRunAway( StateManagerBase& project_state_manager )
 : m_project_state_manager( project_state_manager )
{
}

void ProcessRunAway::Run()
{
    m_project_state_manager.ChangeState( ProjectState_WorldMap );
}

ProcessBase* new_ProcessRunAway(
    StateManagerBase& project_state_manager )
{
    return new ProcessRunAway( project_state_manager );
}

