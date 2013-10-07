#include "SingletonProjectStateManager.hpp"

#include <memory>
#include <assert.h>
#include "System/StateManagerBase.hpp"
#include "Project/State/StateDebugTop.hpp"
#include "Project/State/StateAvaterTest.hpp"
#include "Project/State/StateGameMain.hpp"

namespace {

//! シングルトンインスタンス.
std::auto_ptr<ProjectStateManager> sInstance;

} // namespace unnamed

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

StateBase* ProjectStateManager::new_State( State select_index )
{
    switch( select_index )
    {
    case State_DebugTop:
        return new StateDebugTop();
    case State_AvaterTest:
        return new StateAvaterTest();
    case State_GameMain:
        return new StateGameMain();
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
        "アバターテスト",
        "ゲームメイン",
    };
    return name_list[state];
}

