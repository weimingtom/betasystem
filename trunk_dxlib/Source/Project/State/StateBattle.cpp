#include "System/StateBase.hpp"

#include <assert.h>
#include <memory>
#include <boost/foreach.hpp>
#include "DxLibWrapper/Random.hpp"
#include "DxLibWrapper/ImageLoader.hpp"
#include "DxLibWrapper/SoundLoader.hpp"
#include "DxLibWrapper/LogPrinter.hpp"
#include "DxLibWrapper/Color.hpp"
#include "DxLibWrapper/Graphics.hpp"
#include "DxLibWrapper/Button.hpp"
#include "DxLibWrapper/ReturnVariable.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "Project/CharacterStatus.hpp"
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
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"

class StateBattle : public StateBase
{
public:
    StateBattle( StateManagerBase& project_state_manager );
    
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
    CharacterStatus& m_player;
    State m_state;
    State m_next_state;
    bool m_init;
    std::auto_ptr< LogPrinter > m_log_printer;
    ButtonPtrList m_button_list;
    StateManagerBase& m_project_state_manager;
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

StateBattle::StateBattle( StateManagerBase& project_state_manager )
 : m_map( new_Map( GetBackground() ) )
 , m_player( SaveData::GetInstance().m_player_status )
 , m_log_printer( new_LogPrinter( 240 , 0 ) )
 , m_init( true )
 , m_project_state_manager( project_state_manager )
 , m_on_button( false )
 , m_damage_printer( new_DamagePrinter() )
 , m_break_num(0)
 , m_frame(0)
{
    ChangeState( State_Battle );
//    SingletonSoundLoader::Get()_sound_loader->Play( NameOf( SoundType_WorldMap ) , true );
    InitEnemyList();
}

void StateBattle::Update()
{
    m_state = m_next_state;
    
	InputMouse* m_mouse = SingletonInputMouse::Get();
    m_mouse->Update();
    m_damage_printer->Update();
    switch( m_state )
    {
    case State_Begin:
        if( m_mouse->IsTrig( InputMouse::Type_Left ) )
        {
            ChangeState( State_Battle );
        }
        break;
    case State_Battle:
        UpdateBattle();
        break;
    case State_Lose:
        if( m_mouse->IsTrig( InputMouse::Type_Left ) )
        {
            m_project_state_manager.ChangeState( ProjectState_GameOver );
        }
        break;
    case State_Win:
        if( m_mouse->IsTrig( InputMouse::Type_Left ) )
        {
//            m_project_state_manager.ChangeState( ProjectState_WorldMap );
        }
        break;
    case State_RunAway:
        if( m_mouse->IsTrig( InputMouse::Type_Left ) )
        {
//            m_project_state_manager.ChangeState( ProjectState_Camp );
        }
        break;
    default:
        assert( !"m_state is invalid." );
        exit( ApplicationFailure );
    }
}

void StateBattle::CheckOnButton()
{   
    bool on_button = false;
	Vector2 const mouse_pos = SingletonInputMouse::Get()->Position();
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
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_OnButton ) );
        }else{
//            SingletonSoundLoader::Get()->Play( NameOf( SoundType_ReleaseButton ) );
        }
    }
    m_on_button = on_button;
}

void StateBattle::Draw()
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
		DrawGraph( 50 , 50 , SingletonImageLoader::Get()->ImageHandleOf( NameOf( ImageType_RunAway ) ) );
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

void StateBattle::DrawBattle()
{
    DrawPlayer();
    DrawEnemy();
    DrawButton();
}

void StateBattle::DrawButton()
{
    BOOST_FOREACH( ButtonPtr const& button , m_button_list )
    {
        button->Draw();
    }
}

void StateBattle::DrawBackground()
{
    switch( GetBackground() )
    {
    case BackgroundType_Forest:
		DrawGraph( 0 , 0 , SingletonImageLoader::Get()->ImageHandleOf( NameOf( ImageType_Forest ) ) );
        break;
    case BackgroundType_RedForest:
        DrawGraph( 0 , 0 , SingletonImageLoader::Get()->ImageHandleOf( NameOf( ImageType_RedForest ) ) );
        break;
    }
}

void StateBattle::DrawPlayer()
{
    Vector2 pos( 400 , 230 );
    if( m_player.IsGuard() )
    {
        DrawGraph( pos , SingletonImageLoader::Get()->ImageHandleOf( NameOf( ImageType_Player_Guard ) ) );
    }else{
        DrawGraph( pos , SingletonImageLoader::Get()->ImageHandleOf( NameOf( ImageType_Player ) ) );
    }
}

void StateBattle::DrawEnemy()
{
    for( int i = 0 ; i < m_enemy_max ; i ++ )
    {
        if( m_enemy_list[i] != 0 )
        {
            m_enemy_list[i]->Draw();
        }
    }
}

ButtonPtr StateBattle::new_ButtonRunAway()
{
    Vector2 pos( 500 , 300 );
    Vector2 size( 100 , 100 );
    ButtonPtr result(
        new Button(
            SingletonImageLoader::Get()->ImageHandleOf( NameOf( ImageType_IconRunAway ) ) ,
            pos ,
            size ,
            "RunAway"
        )
    );
    return result;
}

void StateBattle::PlayerAttack( Enemy* enemy )
{
    if( enemy == 0 ){ return; }
    if( !m_player.IsGuard() )
    {
        SingletonSoundLoader::Get()->Play( NameOf( SoundType_Attack ) );
        
        int const damage = m_player.AttackDamage(); 
        enemy->Status().m_hp -= damage;
        m_log_printer->Print( "attack->" + StringOf( damage ) );
        m_damage_printer->Begin( Vector2( 100 , 250 ) , damage );
        
        enemy->Status().m_hp = Clamp( 0 , enemy->Status().m_hp , enemy->Status().m_hp_max );
    }
}

void StateBattle::EnemyAttack( Enemy& enemy )
{
    if( m_player.IsGuard() )
    {
        SingletonSoundLoader::Get()->Play( NameOf( SoundType_SuccessGuard ) );
        int const damage = 0 ;
        m_log_printer->Print( "damaged->" + StringOf( damage ) );
        m_damage_printer->Begin( Vector2( 400 , 250 ) , damage );
    }else{
        SingletonSoundLoader::Get()->Play( NameOf( SoundType_Attack ) );
        int const damage = enemy.Status().m_attack;
        m_player.m_hp -= damage;
        m_log_printer->Print( "damaged->" + StringOf( damage ) );
        m_damage_printer->Begin( Vector2( 400 , 250 ) , damage );
        
        m_player.m_hp = Clamp( 0 , m_player.m_hp , m_player.m_hp_max );
    }
}

void StateBattle::UpdateBattle()
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

void StateBattle::CheckEnd()
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

Enemy* StateBattle::new_Enemy( int index )
{
    if( m_map->HasNextMonster() )
    {
        return new Enemy(
            Vector2( 10 + index * 100 , 270 ) ,
            Vector2( enemy_size , enemy_size ) ,
            SingletonImageLoader::Get()->ImageHandleOf( NameOf( ImageType_Enemy ) ) ,
            m_map->NextMonster()
        );
    }else{
        return 0;
    }
}

void StateBattle::AddEnemy()
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

void StateBattle::InitEnemyList()
{
    for( int i = 0 ; i < m_enemy_max ; i++ )
    {
        m_enemy_list[i] = 0;
    }
}

void StateBattle::UpdateBornMonster()
{
    m_frame++; 
    if( m_frame % 100 == 0 )
    {
        AddEnemy();
    }
}

bool StateBattle::IsGameOver()
{
    return ( m_player.IsDead() );
}

bool StateBattle::IsEndBattle()
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

void StateBattle::UpdatePlayer()
{
	InputMouse* m_mouse = SingletonInputMouse::Get();
    if( m_mouse->IsTrig( InputMouse::Type_Right ) )
    {
        SingletonSoundLoader::Get()->Play( NameOf( SoundType_BeginGuard ) );
    }
    m_player.SetGuard( m_mouse->IsHold( InputMouse::Type_Right ) );
    
    if( m_mouse->IsTrig( InputMouse::Type_Left ) )
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

void StateBattle::UpdateEnemyList()
{
    for( int i = 0 ; i < m_enemy_max ; i++ )
    {
        Enemy* enemy = m_enemy_list[i];
        if( enemy != 0 )
        {
            enemy->Status().m_attack_frame++;
            if( enemy->Status().m_attack_frame > enemy->Status().m_attack_frame_max )
            {
                enemy->Status().m_attack_frame = GetRandToMax( 10 );
                EnemyAttack( *enemy );
            }
        }
    }
}

void StateBattle::PushButton()
{
	InputMouse* m_mouse = SingletonInputMouse::Get();
    if( m_mouse->IsTrig( InputMouse::Type_Left ) )
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

void StateBattle::DrawCharacterStatus( CharacterStatus const& chara , int base_x , int base_y )
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
    
    //ÉAÉ^ÉbÉNÉoÅ[
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
            ColorOf( chara.m_attack_frame * 2 , chara.m_attack_frame * 2 , 0 ) , TRUE );
    }
}

char const* StateBattle::StateNameOf( State state )
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

void StateBattle::ChangeState( State state )
{
    m_next_state = state;
    m_init = true;
}

StateBase* new_StateBattle( StateManagerBase& project_state_manager )
{
    return new StateBattle( project_state_manager );
}

