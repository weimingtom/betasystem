#include "StateSelectStage.hpp"

#include "Project/Draw.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "Project/SaveData.hpp"
#include "Project/Stage.hpp"

StateSelectStage::StateSelectStage( StateManagerBase* manager )
 : m_manager( manager )
 , m_frame(0)
{
    //ボタンを配置する。
    ButtonPtr button( new Button( ImageType_SelectStage1, Vector2(100,100), Vector2(200,100), "Select1" ) );
    m_button_list.push_back( button );

    ButtonPtr button2( new Button( ImageType_SelectStage2, Vector2(100,300), Vector2(200,100), "Select2" ) );
    m_button_list.push_back( button2 );

}

void StateSelectStage::Update()
{
    std::string const button_name = GetButtonName();
    if( button_name == "Select1"){
        gSaveData.m_selected_stage = StageType_ScoreAttack;
    }else if( button_name == "Select2"){
        gSaveData.m_selected_stage = StageType_RedForest;
    }

    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
        if( button_name != ""){
            m_manager->ChangeState( ProjectState_Battle );
        }
    }
}

void StateSelectStage::Draw() const
{
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "ステージ選択画面");
    
    StageInfo const info = StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) );
    DrawFormatString( 0 , 20 , ColorOf(0,255,0) , "stage_name[%s]", info.name);
    
	for( ButtonPtrList::size_type i = 0 ; i < m_button_list.size() ; i++ ){
        m_button_list.at(i)->Draw();
    }
}

std::string StateSelectStage::GetButtonName() const
{
    for( ButtonPtrList::size_type i = 0 ; i < m_button_list.size() ; i++ ){
        Vector2 const mouse_pos = SingletonInputMouse::Get()->Position();
        if( m_button_list.at(i)->CheckHit( mouse_pos ) ){
            return m_button_list.at(i)->Name();
        }
    }
	std::string result = "";
	return result;
}


