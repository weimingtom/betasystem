#include "SingletonStateManager.hpp"

#include <memory>
#include <assert.h>
#include "System/StateManagerBase.hpp"
#include "Project/State/StateDebugTop.hpp"
#include "Project/State/StateLuaTest.hpp"
#include "Project/State/StateDrawTexture.hpp"
#include "Project/State/StateCharacterGenerate.hpp"
#include "Project/State/StateActionGame.hpp"

namespace Princess{

//! �V���O���g���C���X�^���X.
std::auto_ptr<StateManager> sInstance;


StateManager::StateManager()
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
    case State_Action:
		return new StateActionGame();
    case State_LuaTest:
        return new StateLuaTest();
    case State_DrawTexture:
        return new StateDrawTexture();
    case State_CreateChara:
        return new StateCharacterGenerate();
    default:
        assert( !"invalid state");
        return 0;
    }
}


std::string StateManager::NameOf(State state)
{
    static char const* name_list[State_Num] =
    {
        "�f�o�b�O�g�b�v",
        "�A�N�V�����e�X�g",
        "Lua�e�X�g",
        "�摜�`��e�X�g",
        "�L���������e�X�g",
    };
    return name_list[state];
}

} // namespace Princess

