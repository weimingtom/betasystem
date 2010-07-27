#include "System/StateBase.hpp"

#include <assert.h>
#include <memory>
#include <boost/foreach.hpp>
#include "DxLibWrapper/ImageLoader.hpp"
#include "DxLibWrapper/MouseInput.hpp"
#include "DxLibWrapper/LogPrinter.hpp"
#include "DxLibWrapper/Color.hpp"
#include "DxLibWrapper/Graphics.hpp"
#include "DxLibWrapper/Button.hpp"
#include "Project/BattleResult.hpp"
#include "Project/Character.hpp"
#include "Project/AttackContent.hpp"
#include "Project/ProjectImageLoader.hpp"
#include "System/Vector2.hpp"
#include "System/CheckHit.hpp"
#include "System/StringOf.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ProcessBase.hpp"
#include "Project/AttackButtonProcess.hpp"
#include "Project/ProcessRunAway.hpp"


namespace {

ImageType ImageTypeOf( AttackType type )
{
    switch( type )
    {
    case AttackType_Sword:
        return ImageType_Sword;
    case AttackType_Shield:
        return ImageType_Shield;
    case AttackType_Magic:
        return ImageType_Magic;
    default:
        assert( false );
        return ImageType_Sword; // åxçêâÒî.
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
        State_SelectAttackType,
        State_AttackResult,
        State_Win,
        State_Lose,
        State_Num,
    };
    enum CharaType
    {
        CharaType_Player,
        CharaType_Enemy,
        CharaType_Num,
    };
    
private:
    void UpdateSelectAttackType();
    void UpdateAttackResult();
    void UpdateLose();
    void UpdateWin();
    void DrawCharacterStatus( Character chara , int base_x , int base_y );
    void DrawAttackStatus( AttackContent const& attack_list , int base_x , int base_y );
    void DrawBackground();
    void DrawPlayer();
    void DrawEnemy();
    void NextState();
    void Attack();
    char const* StateNameOf( State state );
    void ChangeState( State state );
    static ButtonPtrList AttackButtonPtrListOf(
        Vector2 base_pos ,
        AttackContent& attack_content ,
        ImageLoader& image_loader ,
        CharaType chara_type );
    ButtonPtr new_ButtonRunAway();
    
private:
    std::auto_ptr< ImageLoader > m_image_loader;
    std::auto_ptr< MouseInput > m_mouse;
    Character m_player;
    Character m_enemy;
    State m_state;
    bool m_init;
    AttackContent m_attack_content_list[ CharaType_Num ];
    std::auto_ptr< LogPrinter > m_log_printer;
    ButtonPtrList m_button_list;
    StateManagerBase& m_project_state_manager;
    
};

StateGameMain::StateGameMain( StateManagerBase& project_state_manager )
 : m_image_loader( new_ImageLoader() )
 , m_mouse( new_MouseInput() )
 , m_state( State_SelectAttackType )
 , m_log_printer( new_LogPrinter( 240 , 0 ) )
 , m_init( true )
 , m_project_state_manager( project_state_manager )
{
    ChangeState( State_SelectAttackType );
    m_image_loader->Load();
}

void StateGameMain::Update()
{
    m_mouse->Update();
    
    switch( m_state )
    {
    case State_SelectAttackType:
        UpdateSelectAttackType();
        break;
    case State_AttackResult:
        UpdateAttackResult();
        break;
    case State_Lose:
        UpdateLose();
        break;
    case State_Win:
        UpdateWin();
        break;
    }
}

void StateGameMain::Draw()
{
    DrawBackground();
    DrawFormatString( 0 , 0 , ColorOf() , "State[%s]" , StateNameOf( m_state ) );
    
    switch( m_state )
    {
    case State_SelectAttackType:
        DrawPlayer();
        DrawEnemy();
        BOOST_FOREACH( ButtonPtr const& button , m_button_list )
        {
            button->Draw();
        }
        break;
    case State_AttackResult:
        DrawPlayer();
        DrawEnemy();
        break;
    case State_Lose:
        DrawFormatString( 100 , 100 , ColorOf() , "Lose" );
        DrawEnemy();
        break;
    case State_Win:
        DrawFormatString( 100 , 100 , ColorOf() , "Win" );
        DrawPlayer();
        break;
    }
    
    DrawCharacterStatus( m_player , 330 , 400 );
    DrawAttackStatus( m_attack_content_list[ CharaType_Player ] , 330 , 420 );
    DrawCharacterStatus( m_enemy , 60 , 400 );
    DrawAttackStatus( m_attack_content_list[ CharaType_Enemy ] , 60 , 420 );
    m_log_printer->Draw();
}

void StateGameMain::DrawBackground()
{
    DrawGraph( 0 , 0 , m_image_loader->ImageHandleOf( NameOf( ImageType_Forest ) ) );
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


void StateGameMain::UpdateAttackResult()
{
    if( m_init )
    {
        m_init = false;
        Attack();
    }

    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        NextState();
    }
}

ButtonPtr StateGameMain::new_ButtonRunAway()
{
    Vector2 pos( 500 , 300 );
    Vector2 size( 100 , 100 );
    ButtonPtr result(
        new_Button(
            m_image_loader->ImageHandleOf( NameOf( ImageType_RunAway ) ) ,
            pos ,
            size ,
            new_ProcessRunAway( m_project_state_manager )
        )
    );
    return result;
}

void StateGameMain::UpdateSelectAttackType()
{
    if( m_init )
    {
        m_init = false;
        m_button_list.clear();
        //AttackÇ…ä÷Ç∑ÇÈÉ{É^ÉìÇÃí«â¡.
        for( int i = 0 ; i < CharaType_Num ; i++ )
        {
            ButtonPtrList::iterator const it = m_button_list.begin();
            ButtonPtrList attack_button_list = AttackButtonPtrListOf(
                Vector2( 350 - i * 320 , 20 ),
                m_attack_content_list[ i ] ,
                *m_image_loader ,
                static_cast< CharaType >(i) );
            m_button_list.insert( it , attack_button_list.begin() , attack_button_list.end() );
        }
        m_button_list.push_back( new_ButtonRunAway() );
    }
    
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        Vector2 const mouse_pos = m_mouse->Position();
        
        BOOST_FOREACH( ButtonPtr const& button , m_button_list )
        {
            if( button->CheckHit( mouse_pos ) )
            {
                if( button->HasProcess() )
                {
                    button->Process();
                    ChangeState( State_AttackResult );
                }
            }
        }
    }
}

void StateGameMain::UpdateLose()
{
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        ChangeState( State_SelectAttackType );
    }
}

void StateGameMain::UpdateWin()
{
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        ChangeState( State_SelectAttackType );
    }
}

void StateGameMain::NextState()
{
    if( m_player.m_hp <= 0 )
    {
        ChangeState( State_Lose );
    }
    else if( m_enemy.m_hp <= 0 )
    {
        ChangeState( State_Win );
    }else{
        ChangeState( State_SelectAttackType );
    }
}

void StateGameMain::Attack()
{
    AttackContent const player  = m_attack_content_list[ CharaType_Player ];
    AttackContent const enemy   = m_attack_content_list[ CharaType_Enemy ];
    BattleResult const result =
        BattleResultOf(
            player.m_attack_list[ player.m_select_index ] ,
            enemy.m_attack_list[ enemy.m_select_index ] );
    
    switch( result )
    {
    case BattleResult_Win:
        m_enemy.m_hp -= m_player.m_attack;
        m_log_printer->Print(
            "èüÇø damage -> " + StringOf( m_player.m_attack ) );
        break;
    case BattleResult_Lose:
        m_player.m_hp -= m_enemy.m_attack;
        m_log_printer->Print(
            "ïâÇØ damage -> " + StringOf( m_enemy.m_attack ) );
        break;
    case BattleResult_Draw:
        m_log_printer->Print( "à¯Ç´ï™ÇØ" );
        break;
    default:
        assert( !"invalid case" );
    }
    
    for( int i = 0 ; i < CharaType_Num ; i++ )
    {
        m_attack_content_list[i].PopAttack( m_attack_content_list[i].m_select_index );
    }
}

void StateGameMain::DrawCharacterStatus( Character chara , int base_x , int base_y )
{
    int y = base_y;
    int const margin_y = 20;
    DrawFormatString(
        base_x , y += margin_y ,
        ColorOf() ,
        "hp:[%d]/[%d]" , chara.m_hp , chara.m_hp_max );
}

void StateGameMain::DrawAttackStatus( AttackContent const& attack_list , int base_x , int base_y )
{
    int y = base_y;
    int const margin_y = 20;
    DrawFormatString(
        base_x , y += margin_y ,
        ColorOf() ,
        "action:[%s],[%s],[%s]" ,
        NameOf( attack_list.m_attack_list[0] ),
        NameOf( attack_list.m_attack_list[1] ),
        NameOf( attack_list.m_attack_list[2] ) );
    DrawFormatString(
        base_x , y += margin_y ,
        ColorOf() ,
        "action_next:[%s]" , NameOf( attack_list.m_attack_next ) );
}

char const* StateGameMain::StateNameOf( State state )
{
    static char const* const name[ State_Num ] =
    {
        "çUåÇëIë",
        "çUåÇåãâ ",
        "èüóò",
        "îsñk",
    };
    return name[ state ];
}

void StateGameMain::ChangeState( State state )
{
    m_state = state;
    m_init = true;
}

ButtonPtrList StateGameMain::AttackButtonPtrListOf(
    Vector2 base_pos ,
    AttackContent& attack_content ,
    ImageLoader& image_loader ,
    CharaType chara_type ) 
{
    ButtonPtrList result;
    
    Vector2 const size( 60 , 60 );
    int const margin_x = 80;
    int const margin_y = 80;
    
    //  next_attack.
    {
        Vector2 pos( base_pos.x + margin_x , base_pos.y );
        result.push_back(
            ButtonPtr( new_Button(
                image_loader.ImageHandleOf( NameOf( ImageTypeOf( attack_content.m_attack_next ) ) ),
                pos ,
                size ) ) );
    }
    // attack_list.
    for( int i = 0 ; i < AttackContent::AttackListNum ; i++ )
    {
        ProcessBase* process = 0;
        if( chara_type == CharaType_Player )
        {
            process = new_AttackButtonProcess( i , attack_content );
        }
        Vector2 pos( base_pos.x + i * margin_x , base_pos.y + margin_y );
        result.push_back(
            ButtonPtr( new_Button(
                image_loader.ImageHandleOf( NameOf( ImageTypeOf( attack_content.m_attack_list[i] ) ) ),
                pos ,
                size ,
                process ) ) );
    }
    return result;
}

StateBase* new_StateGameMain( StateManagerBase& project_state_manager )
{
    return new StateGameMain( project_state_manager );
}

