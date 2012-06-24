#include "StateTestMsg.hpp"

#include "Project/Draw.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "Project/SaveData.hpp"

StateTestMsg::StateTestMsg( StateManagerBase* manager )
 : m_manager( manager )
 , m_step( Step_Default )
 , m_frame(0)
{
    gSaveData.Save();
}

void StateTestMsg::Update()
{
    switch( m_step )
    {
    case Step_Default:
        break;
    }
}

void StateTestMsg::Draw() const
{
    switch( m_step )
    {
    case Step_Default:
        DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "メッセージテスト" );
        break;
    }
}

