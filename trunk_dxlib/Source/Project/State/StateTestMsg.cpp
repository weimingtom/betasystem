#include "StateTestMsg.hpp"

#include "Project/Draw.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "Project/Msg/MsgPrinter.hpp"

StateTestMsg::StateTestMsg( StateManagerBase* manager )
 : m_manager( manager )
 , m_step( Step_Default )
 , m_msg_printer( new MsgPrinter() )
{
    m_msg_printer->SetMsg("おはようございます。　こんにちわ。　こんばんわ。");
}

void StateTestMsg::Update()
{
    m_msg_printer->Update();
}

void StateTestMsg::Draw() const
{
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "メッセージテスト遷移" );
    m_msg_printer->Draw();
}

