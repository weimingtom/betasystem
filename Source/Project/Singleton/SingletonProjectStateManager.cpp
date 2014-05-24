#include "SingletonProjectStateManager.hpp"

#include <memory>
#include <assert.h>
#include "System/StateManagerBase.hpp"
#include "Project/State/StateDebugTop.hpp"
#include "Project/State/StateLuaTest.hpp"

namespace Princess{

//! シングルトンインスタンス.
std::auto_ptr<ProjectStateManager> sInstance;


ProjectStateManager::ProjectStateManager()
{
	ChangeState( new_State(State_DebugTop) );
}

ProjectStateManager::~ProjectStateManager()
{
}

ProjectStateManager* ProjectStateManager::GetInstance()
{
    if( !sInstance.get() ){
        sInstance.reset( new ProjectStateManager() );
    }
    return sInstance.get();
}

void ProjectStateManager::DeleteInstance()
{
    sInstance.reset(0);
}

StateBase* ProjectStateManager::new_State( State select_index )
{
    switch( select_index )
    {
    case State_DebugTop:
        return new StateDebugTop();
    case State_LuaTest:
        return new StateLuaTest();
    default:
        assert( !"invalid state");
        return 0;
    }
}


std::string ProjectStateManager::NameOf(State state)
{
    static char const* name_list[State_Num] =
    {
        "デバッグトップ",
        "Luaテスト",
    };
    return name_list[state];
}

} // namespace Princess

