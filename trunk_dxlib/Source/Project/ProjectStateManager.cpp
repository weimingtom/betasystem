#include "Project/ProjectStateManager.hpp"
#include "System/StateManagerBase.hpp"
#include "Project/StateGameMain.hpp"
#include <assert.h>

class ProjectStateManager : public StateManagerBase
{
public:
    ProjectStateManager();
    ~ProjectStateManager();
protected:
    StateBase* new_State( int select_index );
};

ProjectStateManager::ProjectStateManager()
{
}

ProjectStateManager::~ProjectStateManager()
{
}

StateBase* ProjectStateManager::new_State( int select_index )
{
    switch( select_index )
    {
    case ProjectState_Battle:
        return new_StateGameMain();
    default:
        assert( false );
        return 0;
    }
}

StateManagerBase* new_ProjectStateManager()
{
    return new ProjectStateManager();
}

