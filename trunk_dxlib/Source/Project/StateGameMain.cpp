#include "System/StateBase.hpp"

#include <assert.h>
#include <memory>
#include "DxLibWrapper/DxLibWrapper.hpp"
#include "DxLibWrapper/ImageLoader.hpp"
#include "DxLibWrapper/MouseInput.hpp"
#include "DxLibWrapper/Button.hpp"
#include "DxLibWrapper/LogPrinter.hpp"
#include "Project/BattleResult.hpp"
#include "Project/Character.hpp"
#include "Project/AttackContent.hpp"
#include "System/ArraySize.hpp"
#include "System/Vector2.hpp"
#include "System/CheckHit.hpp"


enum ImageType
{
    ImageType_Forest,
    ImageType_Player,
    ImageType_Enemy,
    ImageType_Sword,
    ImageType_Num,
};

char const* const image_name[ ImageType_Num ] =
{
    "Resource/Image.png",
    "Resource/Player.png",
    "Resource/Enemy.png",
    "Resource/Sword.png",
};

class StateGameMain : public StateBase
{
public:
    StateGameMain();
    
public:
    void Update();
    void Draw();
    
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
    
private:
    enum State
    {
        State_SelectAttackType,
        State_AttackResult,
        State_Win,
        State_Lose,
    };
private:
    enum CharaType
    {
        CharaType_Player,
        CharaType_Enemy,
        CharaType_Num,
    };
private:
    std::auto_ptr< ImageLoader > m_image_loader;
    std::auto_ptr< MouseInput > m_mouse;
    Character m_player;
    Character m_enemy;
    State m_state;
    std::auto_ptr< Button > m_button;
    AttackContent m_attack_list[ CharaType_Num ];
    std::auto_ptr< LogPrinter > m_log_printer;
};

StateGameMain::StateGameMain()
 : m_image_loader( new_ImageLoader( image_name , ARRAY_SIZE(image_name) ) )
 , m_mouse( new_MouseInput() )
 , m_state( State_SelectAttackType )
 , m_log_printer( new_LogPrinter( 300 , 20 ) )
{
    m_image_loader->Load();
    m_button.reset(
        new_Button(
            m_image_loader->ImageHandleOf( image_name[ ImageType_Sword ] ) ,
            Vector2(200,200) ,
            Vector2(50,50) ) );
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
    DrawFormatString( 0 , 0 , DefaultFontColor() , "State[%d]" , m_state );
    
    switch( m_state )
    {
    case State_SelectAttackType:
        DrawPlayer();
        DrawEnemy();
        break;
    case State_AttackResult:
        DrawPlayer();
        DrawEnemy();
        break;
    case State_Lose:
        DrawFormatString( 100 , 100 , DefaultFontColor() , "Lose" );
        DrawEnemy();
        break;
    case State_Win:
        DrawFormatString( 100 , 100 , DefaultFontColor() , "Win" );
        DrawPlayer();
        break;
    }
    
    DrawCharacterStatus( m_player , 330 , 400 );
    DrawAttackStatus( m_attack_list[ CharaType_Player ] , 330 , 420 );
    DrawCharacterStatus( m_enemy , 60 , 400 );
    DrawAttackStatus( m_attack_list[ CharaType_Enemy ] , 60 , 420 );
    m_log_printer->Draw();
}

void StateGameMain::DrawBackground()
{
    DrawGraph( 0 , 0 , m_image_loader->ImageHandleOf( image_name[ ImageType_Forest ] ) );
}

void StateGameMain::DrawPlayer()
{
    Vector2 pos( 400 , 230 );
    DrawGraph( pos , m_image_loader->ImageHandleOf( image_name[ ImageType_Player ] ) );
}

void StateGameMain::DrawEnemy()
{
    Vector2 pos( 100 , 290 );
    DrawGraph( pos , m_image_loader->ImageHandleOf( image_name[ ImageType_Enemy ] ) );
}


void StateGameMain::UpdateAttackResult()
{
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        NextState();
    }
}

void StateGameMain::UpdateSelectAttackType()
{
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        Attack();
        m_state = State_AttackResult;
    }
}

void StateGameMain::UpdateLose()
{
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        m_state = State_SelectAttackType;
    }
}

void StateGameMain::UpdateWin()
{
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        m_state = State_SelectAttackType;
    }
}

void StateGameMain::NextState()
{
    if( m_player.m_hp <= 0 )
    {
        m_state = State_Lose;
    }
    else if( m_enemy.m_hp <= 0 )
    {
        m_state = State_Win;
    }else{
        m_state = State_SelectAttackType;
    }
}

void StateGameMain::Attack()
{
    int const select_index = 0;
    AttackType const player_attack = m_attack_list[ CharaType_Player ].GetAction( select_index );
    AttackType const enemy_attack = m_attack_list[ CharaType_Enemy ].GetAction( select_index );
    
    BattleResult const result = BattleResultOf( player_attack , enemy_attack );
    
    switch( result )
    {
    case BattleResult_Win:
        m_enemy.m_hp -= m_player.m_attack;
        m_log_printer->Print( "player attack." );
        break;
    case BattleResult_Lose:
        m_player.m_hp -= m_enemy.m_attack;
        m_log_printer->Print( "enemy attack." );
        break;
    case BattleResult_Draw:
        //‰½‚à‚È‚µ.
        break;
    default:
        assert( !"invalid case" );
    }
}

void StateGameMain::DrawCharacterStatus( Character chara , int base_x , int base_y )
{
    int y = base_y;
    int const margin_y = 20;
    DrawFormatString(
        base_x , y += margin_y ,
        DefaultFontColor() ,
        "hp:[%d]/[%d]" , chara.m_hp , chara.m_hp_max );
}

void StateGameMain::DrawAttackStatus( AttackContent const& attack_list , int base_x , int base_y )
{
    int y = base_y;
    int const margin_y = 20;
    DrawFormatString(
        base_x , y += margin_y ,
        DefaultFontColor() ,
        "action:[%s],[%s],[%s]" ,
        NameOf( attack_list.m_action[0] ),
        NameOf( attack_list.m_action[1] ),
        NameOf( attack_list.m_action[2] ) );
    DrawFormatString(
        base_x , y += margin_y ,
        DefaultFontColor() ,
        "action_next:[%s]" , NameOf( attack_list.m_action_next ) );
}

StateBase* new_StateGameMain()
{
    return new StateGameMain();
}

