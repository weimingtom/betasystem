#include "ProjectStateManager.hpp"

#include <assert.h>
#include "System/StateManagerBase.hpp"
#include "Project/State/StateTitle.hpp"
#include "Project/State/StateAvaterTest.hpp"

/**
    プロジェクトの一番上に位置するStateManager.
*/
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
	ChangeState( ProjectState_Title );
}

ProjectStateManager::~ProjectStateManager()
{
}

StateBase* ProjectStateManager::new_State( int select_index )
{
    switch( select_index )
    {
    case ProjectState_Title:
        return new StateTitle( this );
    case ProjectState_AvaterTest:
    	return new StateAvaterTest(this);
    default:
        assert( false );
        return 0;
    }
}

StateManagerBase* new_ProjectStateManager()
{
    return new ProjectStateManager();
}

