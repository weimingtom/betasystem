#include "SingletonProjectStateManager.hpp"

#include <memory>
#include <assert.h>
#include "System/StateManagerBase.hpp"
#include "Project/State/StateTitle.hpp"
#include "Project/State/StateDebugTop.hpp"

namespace {

//! シングルトンインスタンス.
std::auto_ptr<SingletonProjectStateManager> sInstance;

} // namespace unnamed

SingletonProjectStateManager* SingletonProjectStateManager::GetInstance()
{
    if( !sInstance.get() ){
        sInstance.reset( new SingletonProjectStateManager() );
    }
    return sInstance.get();
}

StateBase* SingletonProjectStateManager::new_State( State select_index )
{
    switch( select_index )
    {
    case State_DebugTop:
        return new StateDebugTop();
    case State_Title:
        return new StateTitle();
    default:
        assert( false );
        return 0;
    }
}

SingletonProjectStateManager::SingletonProjectStateManager()
{
	ChangeState( new_State(State_DebugTop) );
}

SingletonProjectStateManager::~SingletonProjectStateManager()
{
}

