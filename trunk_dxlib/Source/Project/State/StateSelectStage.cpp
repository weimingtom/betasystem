#include "StateSelectStage.hpp"

#include "Project/Draw.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "Project/SaveData.hpp"

StateSelectStage::StateSelectStage( StateManagerBase* manager )
 : m_manager( manager )
 , m_frame(0)
{
}

void StateSelectStage::Update()
{
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
        m_manager->ChangeState( ProjectState_Battle );
    }
}

void StateSelectStage::Draw() const
{
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "ステージ選択画面");
}

