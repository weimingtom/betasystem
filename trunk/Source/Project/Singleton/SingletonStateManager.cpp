#include "SingletonStateManager.hpp"

#include <memory>
#include <assert.h>
#include "Project/State/StateDebugTop.hpp"
#include "Project/State/StateLuaTest.hpp"
#include "Project/State/StateDrawTexture.hpp"
#include "Project/State/StateCharacterGenerate.hpp"
#include "Project/State/StateActionGame.hpp"

namespace Princess{

//! シングルトンインスタンス.
std::auto_ptr<StateManager> sInstance;


StateManager::StateManager()
 : m_current_state(0)
 , m_next_state(0)
{
	ChangeState( new_State(State_DebugTop) );
}

StateManager::~StateManager()
{
}

StateManager* StateManager::GetInstance()
{
    if( !sInstance.get() ){
        sInstance.reset( new StateManager() );
    }
    return sInstance.get();
}

void StateManager::DeleteInstance()
{
    sInstance.reset(0);
}

StateBase* StateManager::new_State( State select_index )
{
    switch( select_index )
    {
    case State_DebugTop:
		return new StateDebugTop();
    case State_DrawTexture:
        return new StateDrawTexture();
    default:
        assert( !"invalid state");
        return 0;
    }
}


std::string StateManager::NameOf(State state)
{
    static char const* name_list[State_Num] =
    {
        "デバッグトップ",
        "アクションテスト",
        "Luaテスト",
        "画像描画テスト",
        "キャラ生成テスト",
    };
    return name_list[state];
}

} // namespace Princess

