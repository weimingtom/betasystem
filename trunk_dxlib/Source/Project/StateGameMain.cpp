#include "System/StateBase.hpp"

#include <assert.h>
#include <memory>
#include <boost/foreach.hpp>
#include "DxLibWrapper/ImageLoader.hpp"
#include "DxLibWrapper/SoundLoader.hpp"
#include "DxLibWrapper/MouseInput.hpp"
#include "DxLibWrapper/LogPrinter.hpp"
#include "DxLibWrapper/Color.hpp"
#include "DxLibWrapper/Graphics.hpp"
#include "DxLibWrapper/Button.hpp"
#include "Project/Character.hpp"
#include "Project/ProjectImageLoader.hpp"
#include "Project/ProjectSoundLoader.hpp"
#include "System/Vector2.hpp"
#include "System/CheckHit.hpp"
#include "System/StringOf.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ProcessBase.hpp"
#include "System/Range.hpp"
#include "Project/ProcessDecideAction.hpp"
#include "Project/ProjectStateManager.hpp"
#include "Project/SaveData.hpp"
#include "Project/CharacterFactory.hpp"
#include "Project/BackgroundFactory.hpp"
#include "Project/Map.hpp"
#include "Project/DamagePrinter.hpp"


namespace {

ImageType ImageTypeOf( AttackType type )
{
    switch( type )
    {
    case AttackType_Normal:
        return ImageType_Sword;
    case AttackType_Guard:
        return ImageType_Shield;
    case AttackType_Special:
        return ImageType_Magic;
    default:
        assert( false );
        exit( ApplicationFailure );
    }
}


} // namespace unnamed

class StateGameMain : public StateBase
{
public:
    StateGameMain( StateManagerBase& project_state_manager );
    
public:
    void Update();
    void Draw();
    
private:
    enum State
    {
        State_Begin,
        State_Battle,
        State_Win,
        State_Lose,
        State_RunAway,
        State_Num,
    };
    enum OperateType
    {
        OperateType_Player,
        OperateType_Enemy,
        OperateType_Num,
    };
    
private:
    void UpdateBattle();
    void UpdatePlayer();
    void UpdateEnemy();
    void PushButton();
    void DrawCharacterStatus( Character const& chara , int base_x , int base_y );
    void DrawBackground();
    void DrawPlayer();
    void DrawEnemy();
    void DrawButton();
    void DrawBattle();
    char const* StateNameOf( State state );
    void ChangeState( State state );
    ButtonPtr new_ButtonRunAway();
    void CheckOnButton();
    void PlayerAttack();
    void EnemyAttack();
    bool IsGameOver();
    bool IsEndBattle();
    void BornMonster();
    void CheckEnd();
    
private:
    std::auto_ptr< MapBase > m_map;
    std::auto_ptr< ImageLoader > m_image_loader;
    std::auto_ptr< MouseInput > m_mouse;
    Character& m_player;
    Character m_enemy;
    State m_state;
    State m_next_state;
    bool m_init;
    std::auto_ptr< LogPrinter > m_log_printer;
    ButtonPtrList m_button_list;
    StateManagerBase& m_project_state_manager;
    std::auto_ptr< SoundLoader > m_sound_loader;
    bool m_on_button;
    int m_frame_enemy;
    std::auto_ptr< DamagePrinter > m_damage_printer;
};

StateGameMain::StateGameMain( StateManagerBase& project_state_manager )
 : m_map( new_Map( GetBackground() ) )
 , m_image_loader( new_ImageLoader() )
 , m_mouse( new_MouseInput() )
 , m_player( SaveData::GetInstance().m_player_status )
 , m_enemy( m_map->NextMonster() )
 , m_log_printer( new_LogPrinter( 240 , 0 ) )
 , m_init( true )
 , m_project_state_manager( project_state_manager )
 , m_sound_loader( new_SoundLoader( SoundFileList() ) )
 , m_on_button( false )
 , m_frame_enemy(0)
 , m_damage_printer( new_DamagePrinter() )
{
    ChangeState( State_Begin );
    m_image_loader->Load();
    m_sound_loader->Load();
//    m_sound_loader->Play( NameOf( SoundType_WorldMap ) , true );
}

void StateGameMain::Update()
{
    m_state = m_next_state;
    
    m_mouse->Update();
    m_damage_printer->Update();
    switch( m_state )
    {
    case State_Begin:
        if( m_mouse->IsTrig( MouseInput::Type_Left ) )
        {
            ChangeState( State_Battle );
        }
        break;
    case State_Battle:
        UpdateBattle();
        break;
    case State_Lose:
        if( m_mouse->IsTrig( MouseInput::Type_Left ) )
        {
            m_project_state_manager.ChangeState( ProjectState_GameOver );
        }
        break;
    case State_Win:
        if( m_mouse->IsTrig( MouseInput::Type_Left ) )
        {
            m_project_state_manager.ChangeState( ProjectState_WorldMap );
        }
        break;
    case State_RunAway:
        if( m_mouse->IsTrig( MouseInput::Type_Left ) )
        {
            m_project_state_manager.ChangeState( ProjectState_Camp );
        }
        break;
    default:
        assert( !"m_state is invalid." );
        exit( ApplicationFailure );
    }
}

void StateGameMain::CheckOnButton()
{   
    bool on_button = false;
    Vector2 const mouse_pos = m_mouse->Position();
    BOOST_FOREACH( ButtonPtr const& button , m_button_list )
    {
        if( button->CheckHit( mouse_pos ) )
        {
            on_button = true;
        }
    }
    
    if( on_button != m_on_button )
    {
        if( on_button )
        {
            m_sound_loader->Play( NameOf( SoundType_OnButton ) );
        }else{
//            m_sound_loader->Play( NameOf( SoundType_ReleaseButton ) );
        }
    }
    m_on_button = on_button;
}

void StateGameMain::Draw()
{
    DrawBackground();
    DrawFormatString( 0 , 0 , ColorOf() , "State[%s]" , StateNameOf( m_state ) );
    m_damage_printer->Draw();
    
    switch( m_state )
    {
    case State_Begin:
        DrawPlayer();
        break;
    case State_Battle:
        DrawBattle();
        break;
    case State_Lose:
        DrawFormatString( 100 , 100 , ColorOf() , "Lose" );
        DrawEnemy();
        break;
    case State_Win:
        DrawFormatString( 100 , 100 , ColorOf() , "Win" );
        DrawPlayer();
        break;
    case State_RunAway:
        DrawGraph( 50 , 50 , m_image_loader->ImageHandleOf( NameOf( ImageType_RunAway ) ) );
        break;
    default:
        assert( !"m_state is invalid." );
        exit( ApplicationFailure );
    }
    
    DrawCharacterStatus( m_player , 330 , 420 );
    DrawCharacterStatus( m_enemy , 60 , 420 );
    m_log_printer->Draw();
}

void StateGameMain::DrawBattle()
{
    DrawPlayer();
    DrawEnemy();
    DrawButton();
    DrawFormatString( 0 , 20 , ColorOf() , "m_frame_enemy[%d]" , m_frame_enemy );
}

void StateGameMain::DrawButton()
{
    BOOST_FOREACH( ButtonPtr const& button , m_button_list )
    {
        button->Draw();
    }
}

void StateGameMain::DrawBackground()
{
    switch( GetBackground() )
    {
    case BackgroundType_Forest:
        DrawGraph( 0 , 0 , m_image_loader->ImageHandleOf( NameOf( ImageType_Forest ) ) );
        break;
    case BackgroundType_RedForest:
        DrawGraph( 0 , 0 , m_image_loader->ImageHandleOf( NameOf( ImageType_RedForest ) ) );
        break;
    }
}

void StateGameMain::DrawPlayer()
{
    Vector2 pos( 400 , 230 );
    DrawGraph( pos , m_image_loader->ImageHandleOf( NameOf( ImageType_Player ) ) );
}

void StateGameMain::DrawEnemy()
{
    Vector2 pos( 100 , 290 );
    DrawGraph( pos , m_image_loader->ImageHandleOf( NameOf( ImageType_Enemy ) ) );
}

ButtonPtr StateGameMain::new_ButtonRunAway()
{
    Vector2 pos( 500 , 300 );
    Vector2 size( 100 , 100 );
    ButtonPtr result(
        new_Button(
            m_image_loader->ImageHandleOf( NameOf( ImageType_IconRunAway ) ) ,
            pos ,
            size ,
            0,
            "RunAway"
        )
    );
    return result;
}

void StateGameMain::PlayerAttack()
{
    int const damage = m_player.AttackDamage(); 
    m_enemy.m_hp -= damage;
    m_log_printer->Print( "attack->" + StringOf( damage ) );
    m_damage_printer->Begin( Vector2( 100 , 250 ) , damage );
    
    m_enemy.m_hp = Clamp( 0 , m_enemy.m_hp , m_enemy.m_hp_max );
    if( m_enemy.IsDead() )
    {
        m_player.m_exp += m_enemy.m_exp;
        if( m_player.CanUpLevel() )
        {
            m_player.UpLevel();
        }
    }
}

void StateGameMain::EnemyAttack()
{
    int const damage = m_enemy.m_attack;
    m_player.m_hp -= damage;
    m_log_printer->Print( "damaged->" + StringOf( damage ) );
    m_damage_printer->Begin( Vector2( 400 , 250 ) , damage );
    
    m_player.m_hp = Clamp( 0 , m_player.m_hp , m_player.m_hp_max );
}

void StateGameMain::UpdateBattle()
{
    if( m_init )
    {
        m_init = false;
        m_frame_enemy = 0;
        m_button_list.push_back( ButtonPtr( new_ButtonRunAway() ) );
    }
    UpdatePlayer();
    UpdateEnemy();
    BornMonster();
    CheckEnd();
    CheckOnButton();
    PushButton();
}

void StateGameMain::CheckEnd()
{
    if( IsGameOver() )
    {
        ChangeState( State_Lose );
    }
    else if( IsEndBattle() )
    {
        ChangeState( State_Win );
    }
}

void StateGameMain::BornMonster()
{
    if( m_enemy.IsDead() )
    {
        if( m_map->HasNextMonster() )
        {
            m_enemy = m_map->NextMonster();
        }
    }
}

bool StateGameMain::IsGameOver()
{
    return ( m_player.IsDead() );
}

bool StateGameMain::IsEndBattle()
{
    return ( m_enemy.IsDead() && !m_map->HasNextMonster() );
}

void StateGameMain::UpdatePlayer()
{
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        PlayerAttack();
    }
}

void StateGameMain::UpdateEnemy()
{
    m_frame_enemy++;
    if( m_frame_enemy % 300 == 0 )
    {
        EnemyAttack();
    }
}

void StateGameMain::PushButton()
{
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
       Vector2 const mouse_pos = m_mouse->Position();
       BOOST_FOREACH( ButtonPtr const& button , m_button_list )
       {
           if( button->CheckHit( mouse_pos ) )
           {
               if( button->Name() == "RunAway" )
               {
                   ChangeState( State_RunAway );
               }
           }
       }
    }
}

void StateGameMain::DrawCharacterStatus( Character const& chara , int base_x , int base_y )
{
    int y = base_y;
    int const margin_y = 12;
    float const gauge_width = 64;
    int const gauge_height = 12;
    int const string_x = base_x + static_cast<int>(gauge_width) + 20;
    
    DrawFormatString(
        string_x , y ,
        ColorOf() ,
        "level:[%d]" , chara.m_level );
    y += margin_y;

    {
        DrawFormatString(
            string_x , y ,
            ColorOf() ,
            "hp:[%d]/[%d]" , chara.m_hp , chara.m_hp_max );
        
        DrawBox(
            base_x , y ,
            static_cast<int>( base_x + gauge_width ), y + gauge_height ,
            ColorOf( 255 , 0 , 0 ) , TRUE ) ;
        float const life_percent = static_cast<float>(chara.m_hp) / chara.m_hp_max;
        DrawBox(
            base_x , y ,
            static_cast<int>( base_x + gauge_width * life_percent ) , y + gauge_height ,
            ColorOf( 0 , 255 , 0 ) , TRUE ) ;
        y += margin_y;
    }
    
    {
        DrawFormatString(
            string_x , y ,
            ColorOf() ,
            "exp:[%d]" , chara.m_exp );
        DrawBox(
            base_x , y ,
            static_cast<int>( base_x + gauge_width ), y + gauge_height ,
            ColorOf( 100 , 100 , 100 ) , TRUE ) ;
        float const percent = static_cast<float>( chara.m_exp ) / chara.m_exp_max;
        DrawBox(
            base_x , y ,
            static_cast<int>( base_x + gauge_width * percent ) , y + gauge_height ,
            ColorOf( 0 , 255 , 0 ) , TRUE ) ;
        y += margin_y;
    }
}

char const* StateGameMain::StateNameOf( State state )
{
    static char const* const name[ State_Num ] =
    {
        "çUåÇëIë",
        "çUåÇåãâ ",
        "èüóò",
        "îsñk",
        "ìGê∂ê¨",
    };
    return name[ state ];
}

void StateGameMain::ChangeState( State state )
{
    m_next_state = state;
    m_init = true;
}

StateBase* new_StateGameMain( StateManagerBase& project_state_manager )
{
    return new StateGameMain( project_state_manager );
}

