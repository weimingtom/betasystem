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
}

void StateTestMsg::Update()
{
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) ){
        m_msg_printer->SetMsg("�y�t�����z\n�͂낤�t���������ł��B[image,]���͂悤�������܂��B[click]\n���s�e�X�g�ł��B�Ă��Ă��B\n[click]����΂��B\n[click]abc");
    }
    m_msg_printer->Update();
    
    if( m_msg_printer->IsEnd() ){
        m_manager->ChangeState( ProjectState_Title );
    }
}

void StateTestMsg::Draw() const
{
    m_msg_printer->Draw();
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "�e�X�g�J��" );
}
