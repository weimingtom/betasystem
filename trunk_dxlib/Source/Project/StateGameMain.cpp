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
        State_SelectAttackType,
        State_AttackResult,
        State_Win,
        State_Lose,
        State_EnemyBorn,
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
    void UpdateSelectAttackType();
    void UpdateAttackResult();
    void DrawCharacterStatus( Character const& chara , int base_x , int base_y );
    void DrawBackground();
    void DrawPlayer();
    void DrawEnemy();
    void NextState();
    void Attack();
    char const* StateNameOf( State state );
    void ChangeState( State state );
    ButtonPtrList AttackButtonPtrListOf(
        Vector2 base_pos ,
        Character const& character ,
        OperateType operate_type );
    ButtonPtr new_ButtonRunAway();
    void CheckOnButton();
    void PlayerAttack();
    void EnemyAttack();
    
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
    bool m_on_process_button;
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
 , m_on_process_button( false )
{
    ChangeState( State_EnemyBorn );
    m_image_loader->Load();
    m_sound_loader->Load();
//    m_sound_loader->Play( NameOf( SoundType_WorldMap ) , true );
}

void StateGameMain::Update()
{
    m_state = m_next_state;
    
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
        if( m_mouse->IsTrig( MouseInput::Type_Left ) )
        {
            m_project_state_manager.ChangeState( ProjectState_GameOver );
        }
        break;
    case State_EnemyBorn:
        if( m_mouse->IsTrig( MouseInput::Type_Left ) )
        {
            if( m_map->HasNextMonster() )
            {
                m_enemy = m_map->NextMonster();
                ChangeState( State_SelectAttackType );
            }else{
                m_project_state_manager.ChangeState( ProjectState_WorldMap );
            }
        }
        break;
    case State_Win:
        if( m_mouse->IsTrig( MouseInput::Type_Left ) )
        {
            ChangeState( State_EnemyBorn );
        }
        break;
    case State_RunAway:
        if( m_mouse->IsTrig( MouseInput::Type_Left ) )
        {
            m_project_state_manager.ChangeState( ProjectState_Camp );
        }
        break;
    }
}

void StateGameMain::CheckOnButton()
{   
    bool on_process_button = false;
    Vector2 const mouse_pos = m_mouse->Position();
    BOOST_FOREACH( ButtonPtr const& button , m_button_list )
    {
        if( button->CheckHit( mouse_pos ) )
        {
            if( button->HasProcess() )
            {
                on_process_button = true;
            }
        }
    }
    
    if( on_process_button != m_on_process_button )
    {
        if( on_process_button )
        {
            m_sound_loader->Play( NameOf( SoundType_OnButton ) );
        }else{
//            m_sound_loader->Play( NameOf( SoundType_ReleaseButton ) );
        }
    }
    m_on_process_button = on_process_button;
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
    case State_EnemyBorn:
        DrawPlayer();
        DrawEnemy();
        break;
    case State_RunAway:
        DrawGraph( 50 , 50 , m_image_loader->ImageHandleOf( NameOf( ImageType_RunAway ) ) );
        break;
    }
    
    DrawCharacterStatus( m_player , 330 , 420 );
    DrawCharacterStatus( m_enemy , 60 , 420 );
    m_log_printer->Draw();
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
    SetDrawBlendMode( DX_BLENDMODE_ALPHA , 200 ) ;
    Vector2 pos( 100 , 290 );
    DrawGraph( pos , m_image_loader->ImageHandleOf( NameOf( ImageType_Enemy ) ) );
    SetDrawBlendMode( DX_BLENDMODE_ALPHA , 255 ) ;
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
            m_image_loader->ImageHandleOf( NameOf( ImageType_IconRunAway ) ) ,
            pos ,
            size ,
            0,
            "RunAway"
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
        {
	        ButtonPtrList::iterator const it = m_button_list.begin();
	        ButtonPtrList attack_button_list = AttackButtonPtrListOf(
	            Vector2( 350 - OperateType_Player * 320 , 20 ),
	            m_player ,
	            OperateType_Player );
	        m_button_list.insert( it , attack_button_list.begin() , attack_button_list.end() );
		}
		{
	        ButtonPtrList::iterator const it = m_button_list.begin();
	        ButtonPtrList attack_button_list = AttackButtonPtrListOf(
	            Vector2( 350 - OperateType_Enemy * 320 , 20 ),
	            m_player ,
	            OperateType_Enemy );
	        m_button_list.insert( it , attack_button_list.begin() , attack_button_list.end() );
		}
        
        m_button_list.push_back( new_ButtonRunAway() );
        m_on_process_button = false;
    }
    
    CheckOnButton();
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        Vector2 const mouse_pos = m_mouse->Position();
        
        BOOST_FOREACH( ButtonPtr const& button , m_button_list )
        {
            if( button->CheckHit( mouse_pos ) )
            {
                if( button->HasProcess() && button->CanProcess() )
                {
                    m_sound_loader->Play( NameOf( SoundType_Decide ) );
                    button->Process();
                    ChangeState( State_AttackResult );
                }
                else if( button->Name() == "RunAway" )
                {
                    ChangeState( State_RunAway );
                }
            }
        }
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
    }
    else
    {
        ChangeState( State_SelectAttackType );
    }
}

void StateGameMain::Attack()
{
    //ÉvÉåÉCÉÑÅ[ÇÃçUåÇ.
    PlayerAttack();
    
    if( !m_enemy.IsLive() )
    {
        m_player.m_exp += m_enemy.m_exp;
        if( m_player.CanUpLevel() )
        {
            m_player.UpLevel();
        }
        return;
    }
    
    EnemyAttack();
}

void StateGameMain::PlayerAttack()
{
    AttackType const attack_type = m_player.m_attack_list[ m_player.m_select_index ] ;
    switch( attack_type )
    {
    case AttackType_Normal:
		{
			int const damage = m_player.AttackDamage();
			m_enemy.m_hp -= damage;
			m_log_printer->Print( "attack->" + StringOf( damage ) );
			break;
		}
    case AttackType_Guard:
        break;
    case AttackType_Special:
		{
			int damage = m_player.AttackDamage() * 2 ;
			m_enemy.m_hp -= damage;
			m_log_printer->Print( "attack->" + StringOf( damage ) );
			break;
		}
    }
    m_player.m_action_point -= NeedPointOf( attack_type );
    m_player.m_action_point = Clamp( 0 , m_player.m_action_point , m_player.m_action_point_max );
    m_enemy.m_hp = Clamp( 0 , m_enemy.m_hp , m_enemy.m_hp_max );
}

void StateGameMain::EnemyAttack()
{
    switch( m_enemy.m_attack_list[ m_enemy.m_select_index ] )
    {
    case AttackType_Normal:
        m_player.m_hp -= m_enemy.m_attack;
        m_log_printer->Print( "damaged->" + StringOf( m_enemy.m_attack ) );
        break;
    case AttackType_Guard:
        break;
    case AttackType_Special:
        m_player.m_hp -= m_enemy.m_attack * 2 ;
        m_log_printer->Print( "damaged->" + StringOf( m_enemy.m_attack * 2 ) );
        break;
    }
    m_player.m_hp = Clamp( 0 , m_player.m_hp , m_player.m_hp_max );
}

void StateGameMain::DrawCharacterStatus( Character const& chara , int base_x , int base_y )
{
    int y = base_y;
    int const margin_y = 12;
    float const gauge_width = 64;
    int const gauge_height = 12;
    DrawBox(
        base_x , y ,
        static_cast<int>( base_x + gauge_width ), y + gauge_height ,
        ColorOf( 255 , 0 , 0 ) , TRUE ) ;
    float const life_percent = static_cast<float>(chara.m_hp) / chara.m_hp_max;
    DrawBox(
        base_x , y ,
        static_cast<int>( base_x + gauge_width * life_percent ) , y + gauge_height ,
        ColorOf( 0 , 255 , 0 ) , TRUE ) ;
    
    DrawFormatString(
        static_cast<int>( base_x + gauge_width ) , y ,
        ColorOf() ,
        "hp:[%d]/[%d]" , chara.m_hp , chara.m_hp_max );
    DrawFormatString(
        base_x , y += margin_y ,
        ColorOf() ,
        "exp:[%d]" , chara.m_exp );
    DrawFormatString(
        base_x , y += margin_y ,
        ColorOf() ,
        "level:[%d]" , chara.m_level );
    DrawFormatString(
        base_x , y += margin_y ,
        ColorOf() ,
        "action_point:[%d]" , chara.m_action_point );
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

ButtonPtrList StateGameMain::AttackButtonPtrListOf(
    Vector2 base_pos ,
    Character const& character ,
    OperateType operate_type ) 
{
    ButtonPtrList result;
    
    Vector2 const size( 60 , 60 );
    int const margin_x = 80;
    int const margin_y = 80;
    
    // attack_list.
    for( int i = 0 ; i < Character::AttackListNum ; i++ )
    {
        ProcessBase* process = 0;
        if( operate_type == OperateType_Player )
        {
            process = new_ProcessDecideAction( i , m_player );
        }
        Vector2 pos( base_pos.x + i * margin_x , base_pos.y + margin_y );
        result.push_back(
            ButtonPtr( new_Button(
                m_image_loader->ImageHandleOf( NameOf( ImageTypeOf( m_player.m_attack_list[i] ) ) ),
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

