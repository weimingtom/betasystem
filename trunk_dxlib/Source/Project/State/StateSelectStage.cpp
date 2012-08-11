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
#include "System/StringOf.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"

StateSelectStage::StateSelectStage( StateManagerBase* manager )
 : m_manager( manager )
 , m_frame(0)
{
    gSaveData.m_player_hp = gSaveData.m_player_max_hp;

    //ボタンを配置する。
    int button_left = 100;
    int const button_width = 100;
    int const button_height = 50;
    int const button_margin = button_height+10;
    int button_top = 100;
    ButtonPtr button( new Button( ImageType_SelectStage1,
        Vector2(button_left,button_top+=button_margin), Vector2(button_width,button_height), "Battle" ) );
    m_button_list.push_back( button );
/*
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
*/
    button_top = 200;
    button.reset( new Button( ImageType_SelectStage2,
        Vector2(button_left,button_top+=button_margin), Vector2(button_width,button_height), "level_up" ) );
    m_button_list.push_back( button );
/*
    button.reset( new Button( ImageType_SelectStage2,
        Vector2(button_left,button_top+=button_margin), Vector2(button_width,button_height), "reset_hp" ) );
    m_button_list.push_back( button );
*/
}

void StateSelectStage::Update()
{
    //毎フレームgSaveDataのstage変えてるのは、ボタンの上にカーソル乗せた時点で、行き先名を表示する必要があるため。
    std::string const button_name = GetButtonName();

    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
        if( button_name.find("Battle") != std::string::npos ){
            m_manager->ChangeState( ProjectState_Battle );
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_Just ) );
		}else if( button_name.find("level_up") != std::string::npos ){
            LevelUp();
		    gSaveData.m_player_hp = gSaveData.m_player_max_hp;
		}else if( button_name.find("reset_hp") != std::string::npos ){
		    gSaveData.m_player_hp = gSaveData.m_player_max_hp;
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_Just ) );
        }
    }
}

void StateSelectStage::LevelUp()
{
    //レベルアップ判定.
    if(gSaveData.m_player_exp > gSaveData.m_player_level*20){
//        std::string log = "レベルが";
//        log += StringOf(gSaveData.m_player_level);
//        log += "に上がった。";
//        m_log_printer->Print(log,ColorOf(255,0,0));
        gSaveData.m_player_exp -= gSaveData.m_player_level*15;
        gSaveData.m_player_level++;
        gSaveData.m_player_max_hp+=5*gSaveData.m_player_level;
        SingletonSoundLoader::Get()->Play( NameOf( SoundType_Just ) );
    }

}

void StateSelectStage::Draw() const
{
    DrawTexture( Vector2(0,0), ImageType_SelectStage );

    DrawFormatString( 0 , 0 , ColorOf(0,0,0) , "ステージ選択画面");
    
    StageInfo const info = StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) );
    DrawFormatString( 0 , 20 , ColorOf(0,0,0) , "stage_name[%s]", info.name);
	DrawFormatString( 0 , 40 , ColorOf(0,0,0) , "level[%d]", gSaveData.m_player_level);
	DrawFormatString( 0 , 60 , ColorOf(0,0,0) , "exp[%d]", gSaveData.m_player_exp);
	DrawFormatString( 0 , 80 , ColorOf(0,0,0) , "hp[%d/%d]", gSaveData.m_player_hp, gSaveData.m_player_max_hp );
    
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


