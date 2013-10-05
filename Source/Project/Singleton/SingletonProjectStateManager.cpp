#include "SingletonProjectStateManager.hpp"

#include <assert.h>
#include "System/StateManagerBase.hpp"
#include "Project/State/StateTitle.hpp"
#include "Project/State/StateAvaterTest.hpp"

namespace {

//! シングルトンインスタンス.
static SingletonProjectStateManager* sInstance = NULL;

} // namespace unnamed

SingletonProjectStateManager* SingletonProjectStateManager::GetInstance()
{
    if( sInstance == NULL ){
        sInstance = new SingletonProjectStateManager();
    }
    return sInstance;
}

StateBase* SingletonProjectStateManager::new_State( State select_index )
{
    switch( select_index )
    {
    case State_DebugTop:
        return new StateTitle();
    case State_Title:
        return new StateTitle();
    default:
        assert( false );
        return 0;
    }
}

SingletonProjectStateManager::SingletonProjectStateManager()
{
	ChangeState( new_State(State_Title) );
}

SingletonProjectStateManager::~SingletonProjectStateManager()
{
}

