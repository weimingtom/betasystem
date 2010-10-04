#include "System/StateBase.hpp"

#include <assert.h>
#include <memory>
#include <boost/foreach.hpp>
#include "DxLibWrapper/Random.hpp"
#include "DxLibWrapper/ImageLoader.hpp"
#include "DxLibWrapper/SoundLoader.hpp"
#include "DxLibWrapper/MouseInput.hpp"
#include "DxLibWrapper/LogPrinter.hpp"
#include "DxLibWrapper/Color.hpp"
#include "DxLibWrapper/Graphics.hpp"
#include "DxLibWrapper/Button.hpp"
#include "Project/CharacterStatus.hpp"
#include "Project/ProjectImageLoader.hpp"
#include "Project/ProjectSoundLoader.hpp"
#include "System/Vector2.hpp"
#include "System/CheckHit.hpp"
#include "System/StringOf.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ProcessBase.hpp"
#include "System/Range.hpp"
#include "Project/ProjectStateManager.hpp"
#include "Project/SaveData.hpp"
#include "Project/CharacterStatusFactory.hpp"
#include "Project/BackgroundFactory.hpp"
#include "Project/Map.hpp"
#include "Project/DamagePrinter.hpp"
#include "Project/Enemy.hpp"

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
    
private:
    void UpdateBattle();
    void UpdatePlayer();
    void UpdateEnemyList();
    void PushButton();
    void DrawCharacterStatus( CharacterStatus const& chara , int base_x , int base_y );
    void DrawBackground();
    void DrawPlayer();
    void DrawEnemy();
    void DrawButton();
    void DrawBattle();
    char const* StateNameOf( State state );
    void ChangeState( State state );
    ButtonPtr new_ButtonRunAway();
    void CheckOnButton();
    void PlayerAttack( Enemy* enemy );
    void EnemyAttack( Enemy& enemy );
    bool IsGameOver();
    bool IsEndBattle();
    void UpdateBornMonster();
    void CheckEnd();
    Enemy* new_Enemy( int index );
    void AddEnemy();
    void InitEnemyList();
    
private:
    std::auto_ptr< MapBase > m_map;
    std::auto_ptr< ImageLoader > m_image_loader;
    std::auto_ptr< MouseInput > m_mouse;
    CharacterStatus& m_player;
    State m_state;
    State m_next_state;
    bool m_init;
    std::auto_ptr< LogPrinter > m_log_printer;
    ButtonPtrList m_button_list;
    StateManagerBase& m_project_state_manager;
    std::auto_ptr< SoundLoader > m_sound_loader;
    bool m_on_button;
    std::auto_ptr< DamagePrinter > m_damage_printer;
    static int const enemy_x = 200;
    static int const enemy_y = 200;
    static int const enemy_size = 100;
    int m_break_num;
    static int const m_enemy_max = 3;
    Enemy* m_enemy_list[ m_enemy_max ];
    int m_frame;
};

StateGameMain::StateGameMain( StateManagerBase& project_state_manager )
 : m_map( new_Map( GetBackground() ) )
 , m_image_loader( new_ImageLoader() )
 , m_mouse( new_MouseInput() )
 , m_player( SaveData::GetInstance().m_player_status )
 , m_log_printer( new_LogPrinter( 240 , 0 ) )
 , m_init( true )
 , m_project_state_manager( project_state_manager )
 , m_sound_loader( new_SoundLoader( SoundFileList() ) )
 , m_on_button( false )
 , m_damage_printer( new_DamagePrinter() )
 , m_break_num(0)
 , m_frame(0)
{
    ChangeState( State_Begin );
    m_image_loader->Load();
    m_sound_loader->Load();
//    m_sound_loader->Play( NameOf( SoundType_WorldMap ) , true );
    InitEnemyList();
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
    DrawFormatString( 0 , 0 , ColorOf() , "m_break_num[%d]" , m_break_num );
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
    for( int i = 0 ; i < m_enemy_max ; i++ )
    {
        Enemy* enemy = m_enemy_list[i];
        if( enemy != 0 )
        {
            DrawCharacterStatus( enemy->Status() , static_cast<int>( enemy->m_pos.x ) , static_cast<int>( enemy->m_pos.y ) );
        }
    }
    m_log_printer->Draw();
}

void StateGameMain::DrawBattle()
{
    DrawPlayer();
    DrawEnemy();
    DrawButton();
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
    if( m_player.IsGuard() )
    {
        DrawGraph( pos , m_image_loader->ImageHandleOf( NameOf( ImageType_Player_Guard ) ) );
    }else{
        DrawGraph( pos , m_image_loader->ImageHandleOf( NameOf( ImageType_Player ) ) );
    }
}

void StateGameMain::DrawEnemy()
{
    for( int i = 0 ; i < m_enemy_max ; i ++ )
    {
        if( m_enemy_list[i] != 0 )
        {
            m_enemy_list[i]->Draw();
        }
    }
}

ButtonPtr StateGameMain::new_ButtonRunAway()
{
    Vector2 pos( 500 , 300 );
    Vector2 size( 100 , 100 );
    ButtonPtr result(
        new Button(
            m_image_loader->ImageHandleOf( NameOf( ImageType_IconRunAway ) ) ,
            pos ,
            size ,
            "RunAway"
        )
    );
    return result;
}

void StateGameMain::PlayerAttack( Enemy* enemy )
{
    if( enemy == 0 ){ return; }
    if( !m_player.IsGuard() )
    {
        m_sound_loader->Play( NameOf( SoundType_Attack ) );
        
        int const damage = m_player.AttackDamage(); 
        enemy->Status().m_hp -= damage;
        m_log_printer->Print( "attack->" + StringOf( damage ) );
        m_damage_printer->Begin( Vector2( 100 , 250 ) , damage );
        
        enemy->Status().m_hp = Clamp( 0 , enemy->Status().m_hp , enemy->Status().m_hp_max );
    }
}

void StateGameMain::EnemyAttack( Enemy& enemy )
{
    if( m_player.IsGuard() )
    {
        m_sound_loader->Play( NameOf( SoundType_SuccessGuard ) );
        int const damage = 0 ;
        m_log_printer->Print( "damaged->" + StringOf( damage ) );
        m_damage_printer->Begin( Vector2( 400 , 250 ) , damage );
    }else{
        m_sound_loader->Play( NameOf( SoundType_Attack ) );
        int const damage = enemy.Status().m_attack;
        m_player.m_hp -= damage;
        m_log_printer->Print( "damaged->" + StringOf( damage ) );
        m_damage_printer->Begin( Vector2( 400 , 250 ) , damage );
        
        m_player.m_hp = Clamp( 0 , m_player.m_hp , m_player.m_hp_max );
    }
}

void StateGameMain::UpdateBattle()
{
    if( m_init )
    {
        m_init = false;
        m_button_list.push_back( ButtonPtr( new_ButtonRunAway() ) );
    }
    UpdatePlayer();
    UpdateEnemyList();
    UpdateBornMonster();
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

Enemy* StateGameMain::new_Enemy( int index )
{
    if( m_map->HasNextMonster() )
    {
        return new Enemy(
            Vector2( 10 + index * 100 , 300 ) ,
            Vector2( enemy_size , enemy_size ) ,
            m_image_loader->ImageHandleOf( NameOf( ImageType_Enemy ) ) ,
            m_map->NextMonster()
        );
    }else{
        return 0;
    }
}

void StateGameMain::AddEnemy()
{
    for( int i = 0 ; i < m_enemy_max ; i++ )
    {
        if( m_enemy_list[i] == 0 )
        {
            m_enemy_list[i] = new_Enemy(i);
            return;
        }
    }
}

void StateGameMain::InitEnemyList()
{
    for( int i = 0 ; i < m_enemy_max ; i++ )
    {
        m_enemy_list[i] = 0;
    }
}

void StateGameMain::UpdateBornMonster()
{
    m_frame++; 
    if( m_frame % 100 == 0 )
    {
        AddEnemy();
    }
}

bool StateGameMain::IsGameOver()
{
    return ( m_player.IsDead() );
}

bool StateGameMain::IsEndBattle()
{
    for( int i = 0 ; i < m_enemy_max ; i++ )
    {
        if( m_enemy_list[i] != 0 )
        {
            return false;
        }
    }
    return ( !m_map->HasNextMonster() );
}

void StateGameMain::UpdatePlayer()
{
    if( m_mouse->IsTrig( MouseInput::Type_Right ) )
    {
        m_sound_loader->Play( NameOf( SoundType_BeginGuard ) );
    }
    m_player.SetGuard( m_mouse->IsHold( MouseInput::Type_Right ) );
    
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        Vector2 const pos = m_mouse->Position();
        for( int i = 0 ; i < m_enemy_max ; i ++ )
        {
            #define ENEMY m_enemy_list[i]
            if( ENEMY != 0 )
            {
                if( ENEMY->CheckHit( pos ) )
                {
                    PlayerAttack( ENEMY );
                    if( ENEMY->Status().IsDead() )
                    {
                        delete ENEMY;
                        ENEMY = 0;
                        m_break_num++;
                    }
                    break;
                }
            }
        }
    }
}

void StateGameMain::UpdateEnemyList()
{
    for( int i = 0 ; i < m_enemy_max ; i++ )
    {
        Enemy* enemy = m_enemy_list[i];
        if( enemy != 0 )
        {
            enemy->Status().m_attack_frame++;
            if( enemy->Status().m_attack_frame > enemy->Status().m_attack_frame_max )
            {
                enemy->Status().m_attack_frame = 0;
                EnemyAttack( *enemy );
            }
        }
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

void StateGameMain::DrawCharacterStatus( CharacterStatus const& chara , int base_x , int base_y )
{
    int y = base_y;
    int const margin_y = 12;
    float const gauge_width = 64;
    int const gauge_height = 12;
    int const string_x = base_x;
    
    y += margin_y;
    {
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
        DrawFormatString(
            string_x , y ,
            ColorOf() ,
            "hp:[%d]/[%d]" , chara.m_hp , chara.m_hp_max );
    }
    
    //�A�^�b�N�o�[
    {
        int const width = 64;
        int const height = 12;
        DrawBox(
            base_x , base_y ,
            base_x + width , base_y + height ,
            ColorOf(10,10,10) , TRUE );
        DrawBox(
            base_x , base_y ,
            static_cast<int>( base_x + width * ( static_cast<float>( chara.m_attack_frame ) / chara.m_attack_frame_max ) ) , base_y + height ,
            ColorOf(200,200,0) , TRUE );
    }
}

char const* StateGameMain::StateNameOf( State state )
{
    static char const* const name[ State_Num ] =
    {
        "�U���I��",
        "�U������",
        "����",
        "�s�k",
        "�G����",
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

