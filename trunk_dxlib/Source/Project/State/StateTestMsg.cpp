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
 , m_chara_drawer( new CharacterDrawer() )
{
	m_chara_drawer->SetChara( ImageType_StandFuriru, CharacterDrawer::CharaPos_Left );
}

void StateTestMsg::Update()
{
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) ){
        m_msg_printer->SetMsg("おはようございます。[click]\n改行テストです。てすてす。\n[click]こんばんわ。\n[click]abc");
    }
    m_msg_printer->Update();
    m_chara_drawer->Update();
}

void StateTestMsg::Draw() const
{
    m_chara_drawer->Draw();
    m_msg_printer->Draw();
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "テスト遷移" );
}

