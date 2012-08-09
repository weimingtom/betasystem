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
    int const button_left = 100;
    int const button_width = 100;
    int const button_height = 50;
    int const button_margin = button_height+10;
    int button_top = 10;
    ButtonPtr button( new Button( ImageType_SelectStage1,
        Vector2(button_left,button_top+=button_margin), Vector2(button_width,button_height), "Select1" ) );
    m_button_list.push_back( button );
    button.reset( new Button( ImageType_SelectStage2,
        Vector2(button_left,button_top+=button_margin), Vector2(button_width,button_height), "Select2" ) );
    m_button_list.push_back( button );
    button.reset( new Button( ImageType_SelectStage2,
        Vector2(button_left,button_top+=button_margin), Vector2(button_width,button_height), "Select3" ) );
    m_button_list.push_back( button );
    button.reset( new Button( ImageType_SelectStage2,
        Vector2(button_left,button_top+=button_margin), Vector2(button_width,button_height), "Select4" ) );
    m_button_list.push_back( button );
    button.reset( new Button( ImageType_SelectStage2,
        Vector2(button_left,button_top+=button_margin), Vector2(button_width,button_height), "Select5" ) );
    m_button_list.push_back( button );

}

void StateSelectStage::Update()
{
    std::string const button_name = GetButtonName();
    if( button_name == "Select1"){
        gSaveData.m_selected_stage = StageType_ScoreAttack;
    }else if( button_name == "Select2"){
        gSaveData.m_selected_stage = StageType_RedForest;
    }else if( button_name == "Select3"){
        gSaveData.m_selected_stage = StageType_WhiteForest;
    }else if( button_name == "Select4"){
        gSaveData.m_selected_stage = StageType_4;
    }else if( button_name == "Select5"){
        gSaveData.m_selected_stage = StageType_5;
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
    DrawTexture( Vector2(0,0), ImageType_SelectStage );

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


