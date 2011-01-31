#include "Project/ProjectStateManager.hpp"

#include <assert.h>
#include "System/StateManagerBase.hpp"
#include "Project/StateBattle.hpp"
#include "Project/StateWorldMap.hpp"
#include "Project/StateCamp.hpp"
#include "Project/StateGameOver.hpp"

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
    case ProjectState_WorldMap:
        return new_StateWorldMap( *this );
    case ProjectState_Battle:
        return new_StateBattle( *this );
    case ProjectState_Camp:
        return new_StateCamp( *this );
    case ProjectState_GameOver:
        return new_StateGameOver( *this );
    default:
        assert( false );
        return 0;
    }
}

StateManagerBase* new_ProjectStateManager()
{
    return new ProjectStateManager();
}

