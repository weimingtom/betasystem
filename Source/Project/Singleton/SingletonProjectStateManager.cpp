#include "SingletonProjectStateManager.hpp"

#include <memory>
#include <assert.h>
#include "System/StateManagerBase.hpp"
#include "Project/State/StateDebugTop.hpp"
#include "Project/State/StateAvaterTest.hpp"
#include "Project/State/StateGameMain.hpp"
#include "Project/State/StatePaletteTest.hpp"
#include "Project/State/StateEquipTest.hpp"
#include "Project/State/StateBattle.hpp"

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
    case State_AvaterTest:
        return new StateAvaterTest();
    case State_GameMain:
        return new StateGameMain();
    case State_PaletteTest:
        return new StatePaletteTest();
    case State_EquipTest:
        return new StateEquipTest();
    case State_Battle:
        return new StateBattle();
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
        "パレットテスト",
        "装備テスト",
        "戦闘画面",
    };
    return name_list[state];
}

