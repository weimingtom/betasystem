#include "StateBattle.hpp"

#include "System/StateManagerBase.hpp"
#include "System/Camera.hpp"
#include "System/Range.hpp"
#include "System/StringOf.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "DxLibWrapper/Random.hpp"
#include "DxLibWrapper/AnimTexture.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Draw.hpp"
#include "Project/ScrollBackground.hpp"
#include "Project/AnimData.hpp"
#include "Project/SaveData.hpp"
#include "Project/PlayerLife.hpp"
#include "Project/BreakEnemyCounter.hpp"
#include <math.h>
#include "Gauge.hpp"

StateBattle::StateBattle( StateManagerBase& manager )
 : m_manager( manager )
 , m_background( new ScrollBackground() )
 , m_frame(0)
 , m_camera( new Camera() )
 , m_player_texture( new AnimTexture(
    ImageHandleOf( ImageType_Player ), AnimDataOf( AnimType_PlayerIdling ) ) )
 , mPlayerLife( new PlayerLife(1) )
 , mBreakEnemyCounter( new BreakEnemyCounter() )
 , m_stage_info( StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) ) )
 , m_is_debug_draw( false )
 , m_msg_printer( new MsgPrinter() )
 , m_log_printer( new_LogPrinter(50,70) )
{
    m_player_pos.y = 300;
    InitEnemy();
    InitPreTalk();
    
    gSaveData.m_player_hp = gSaveData.m_player_max_hp;
}

StateBattle::~StateBattle()
{
}

void StateBattle::Update()
{
    UpdateDebug();
    UpdateCommon();
	switch( m_step )
	{
	case Step_PreTalk:
	    if( m_msg_printer->IsEnd() ){
	        SetStep( Step_Dash );
	    }
	    break;
	case Step_Dash:
		StepDash();
		break;
    case Step_DashEnd:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
            InitResult();
	    }
        break;
	case Step_Result:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
            UpdateHiScore();
            gSaveData.Reset(); // セーブデータ消去.
	    	m_manager.ChangeState( ProjectState_Title );
	    }
		break;
    case Step_Clear:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	        gSaveData.m_selected_stage++;
    	    m_manager.ChangeState( ProjectState_Battle );
    	    UpdateHiScore();
        }
        break;
	}
}

void StateBattle::Draw() const
{
    //背景色のリセット.
    DrawBox( 0, 0, 640 , 480, GetColor( 200,222,200 ), TRUE );
    m_background->Draw( m_camera->Position() );
    m_player_texture->Draw( m_camera->Position() );
	//敵の描画.
    for( int i = 0 ; i < m_stage_info.total_enemy ; i++ ){
        if( m_enemy[i]->IsVisible() ){
            m_enemy[i]->Draw( m_camera->Position() );
        }
    }

    switch( m_step )
    {
    case Step_DecideMeter:
        DrawDashGauge();
		//説明
        DrawTexture( Vector2(120,100), ImageType_Explain );
        break;
    case Step_Dash:
        //倍速
        if( SingletonInputMouse::Get()->IsHold( InputMouse::Type_Right ) ){
            DrawFormatString( 600 , 10 , ColorOf() , "×２" );
        }
        break;
	case Step_WaitDash:
        DrawDashGauge();
        break;
    case Step_DashEnd:
        DrawFormatString( 250 , 200 , ColorOf() , "やられたー" );
        break;
    case Step_Result:
        DrawFormatString( 250 , 200 , ColorOf() , "がめおべら" );
        break;
    case Step_Clear:
        DrawFormatString( 250 , 200 , ColorOf() , "ステージクリア！");
        break;
    }
    //mBreakEnemyCounter->Draw();
    DrawItem();
    //mPlayerLife->Draw();
	m_msg_printer->Draw();
    
	{
		//HP表示.
		int x = 10,y = 460;
		int width = gSaveData.m_player_max_hp;
		int height = 20;
		DrawBox( x, y, x+width , y+height, GetColor( 0,0,0 ), TRUE );
		DrawBox( x, y, x+gSaveData.m_player_hp , y+height, GetColor( 0,255,0 ), TRUE );
	}

    m_log_printer->Draw();

    DrawDebug();
}

void StateBattle::SetStep( Step step )
{
	m_step = step;
}

void StateBattle::InitStepWaitDash()
{
    SetStep( Step_WaitDash );
    m_frame = 0;
	gSaveData.m_player_hp += m_gauge->GetValue();
    m_player_texture->Set( AnimDataOf( AnimType_PlayerCharge ) );
}

void StateBattle::StepWaitDash()
{
    m_frame++;
    if( m_frame > 100 ){
        m_player_texture->Set( AnimDataOf( AnimType_PlayerDash ) );
        SetStep( Step_Dash );
    }
}

/**
    ダメージ計算.
*/
int DamageOf(ManaType player_mana_type,Enemy* enemy)
{
    int result = enemy->GetHP();
    switch( player_mana_type )
    {
    case ManaType_Red:
        if( enemy->GetManaType() == ManaType_Blue ){ result *= 2; }
        if( enemy->GetManaType() == ManaType_Green){ result/=2; }
        break;
    case ManaType_Green:
        if( enemy->GetManaType() == ManaType_Red ){ result *= 2; }
        if( enemy->GetManaType() == ManaType_Blue){ result/=2; }
        break;
    case ManaType_Blue:
        if( enemy->GetManaType() == ManaType_Green ){ result *= 2; }
        if( enemy->GetManaType() == ManaType_Red ){ result/=2; }
        break;
    }
	return result;
}

void StateBattle::StepDash()
{
    UseItem();

    //クリックしたら進む
    if( SingletonInputMouse::Get()->IsHold( InputMouse::Type_Left ) ){
        m_player_pos.x += 20.0f;
    }

    if( SingletonInputMouse::Get()->IsHold( InputMouse::Type_Right ) ){
        m_player_pos.x += 30.0f;
    }

    /**
        プレイヤーと敵がぶつかったら、敵をふっとばす.
    */
    for( int i = 0 ; i < m_stage_info.total_enemy ; i++ ){
        if( m_enemy[i]->IsAlive() ){
            if( m_enemy[i]->Position().x < m_player_pos.x ){
                gSaveData.m_player_hp -= DamageOf( static_cast<ManaType>(gSaveData.m_player_mana_type) , m_enemy[i].get() );
                SingletonSoundLoader::Get()->Play( NameOf( SoundType_OK ) );
                m_enemy[i]->SetSpeed( Vector2( 20.0f * 2, - GetRand(20)-3 ) );
                m_enemy[i]->SetAlive( false );
                mBreakEnemyCounter->Add();
                gSaveData.m_total_break++;
                gSaveData.m_player_exp += m_enemy[i]->GetExp();
                GetItem();
            }
        }
    }
    
    //ゲームオーバー判定.
	if( gSaveData.m_player_hp <= 0 ){
		m_player_texture->Set( AnimDataOf( AnimType_PlayerDeath ) );
		SetStep( Step_DashEnd );
	}
	//クリア判定.
    if( RemainEnemy() == 0 ){
        SetStep( Step_Clear );
    }
}

/**
    デバッグ情報描画.
*/
void StateBattle::DrawDebug() const
{
    int const x = 400;
    int y = 10;
    DrawFormatString( x , y+=20,    ColorOf() , "max_hp[%d]", gSaveData.m_player_max_hp);
    DrawFormatString( x , y+=20,    ColorOf() , "hp[%d]", gSaveData.m_player_hp);
    DrawFormatString( x , y+=20,    ColorOf() , "m_player_exp[%d]", gSaveData.m_player_exp);
    DrawFormatString( x , y+=20,    ColorOf() , "m_player_level[%d]", gSaveData.m_player_level);
    StageInfo const info = StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) );
    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "stage_name[%s]", info.name);
    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "m_player_mana_type[%s]", NameOf( static_cast<ManaType>(gSaveData.m_player_mana_type)) );
    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "進行度");
    
    float width = 200.0f;
	int height = 20;
	DrawBox( x , y+=20, static_cast<int>(x+width) , y+height, GetColor( 0,255,0 ), TRUE );
	DrawBox( x , y, static_cast<int>(x+width*(float)mBreakEnemyCounter->Num()/info.total_enemy) , y+height, GetColor( 255,0,0 ), TRUE );

    for( int i = 0 ; i < ItemType_Num ; i++ ){
        DrawFormatString( i*50 , 50 , ColorOf(0,0,0) , "[%d]" , gSaveData.m_item[i] );
    }

}

/**
    ゲージの描画
*/
void StateBattle::DrawDashGauge() const
{
    DrawGauge( 10 , 410 + 25 );
}

void StateBattle::DrawGauge( int x, int y) const
{
	int const height = 20;
	//下地
	DrawBox( x, y, x+m_gauge->GetMax() , y+height, GetColor( 0,0,0 ), TRUE );
	
	int const color = GetColor( 0, static_cast<int>(255.0f / m_gauge->GetMax() * m_gauge->GetValue()), 0 );
	DrawBox( x, y, x+m_gauge->GetValue() , y+height, color, TRUE );
}

void StateBattle::UpdateCommon()
{
    m_player_texture->Update();
    m_player_texture->Set( m_player_pos );
    //敵更新
    for( int i = 0 ; i < m_stage_info.total_enemy ; i++ ){
        if( m_enemy[i]->IsVisible() ){
            m_enemy[i]->Update();
        }
    }
    //カメラはプレイヤー追尾.
	m_camera->SetPosition( m_player_pos - Vector2( 640/2 - 200, 480/2 + 50 ) );
	//背景スクロール
    m_background->SetScroll( m_camera->Position() );

    m_msg_printer->Update();
}

void StateBattle::InitResult()
{
	SetStep( Step_Result );
	m_player_texture->Set( AnimDataOf( AnimType_PlayerGrave ) );
}

void StateBattle::InitPreTalk()
{
    m_step = Step_PreTalk;
    
    int const msg_num = 3;
    int const rand_num = GetRandToMax(msg_num); 
    char const* pre_message[msg_num] = {
        "[image,]【フリル】\nぉお、大量におるな。[click]頑張るとするかね。[click][clear]",
        "[image,]【フリル】\nおいしそうなスライムが一杯だ。[click]やる気出てきた。[click][clear]",
        "[image,]【フリル】\nうぁ、眠い。[click]適当に頑張る。[click][clear]",
    };
    m_msg_printer->SetMsg(pre_message[rand_num]);
}

/**
    メーター決定への遷移.
    全て初期化.
*/
void StateBattle::InitStepDecideMeter()
{
    SetStep( Step_DecideMeter );
    m_gauge.reset( new Gauge(gSaveData.m_player_max_hp) );
	m_player_texture->Set( AnimDataOf( AnimType_PlayerIdling ) );
}

void StateBattle::StepDecideMeter()
{
	m_gauge->Update(SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ));

	if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
		//連打音.
        SingletonSoundLoader::Get()->Play( NameOf( SoundType_OK ) );
	}

	if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) )
    {
	    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Just ) );
        InitStepWaitDash();
    }
}

/**
    アイテムの使用.
*/
void StateBattle::UseItem()
{
    for( int i = 0 ; i < ItemType_Num ; i++ ){
        if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_F1 + i ) ) )
        {
            if( gSaveData.m_item[i] != 0 ){
                gSaveData.m_item[i]--;

                std::string log = NameOf( static_cast<ItemType>(i) );
                log += "を使った。";
                m_log_printer->Print(log);
                UseItem( static_cast<ItemType>( i ) );
            }
        }
    }
}

void StateBattle::UseItem( ItemType type )
{
	switch( type ){
    case ItemType_Meet:
        gSaveData.m_player_hp += 5;
        break;
    case ItemType_GoodMeet:
        gSaveData.m_player_hp += 20;
        break;
    case ItemType_LifeWater:
        gSaveData.m_player_max_hp += 10;
        break;
    case ItemType_RedManaStone:
        gSaveData.m_player_mana_type = ManaType_Red;
        break;
    case ItemType_GreenManaStone:
        gSaveData.m_player_mana_type = ManaType_Green;
        break;
    case ItemType_BlueManaStone:
        gSaveData.m_player_mana_type = ManaType_Blue;
        break;
    }
    gSaveData.m_player_hp = Clamp(0,gSaveData.m_player_hp,gSaveData.m_player_max_hp);
    
    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Item ) );
}

int StateBattle::RemainEnemy() const
{
    int remain_enemy = 0;
    for( int i = 0 ; i < m_stage_info.total_enemy ; i++ ){
        if( m_enemy[i]->IsAlive() ){
            remain_enemy++;
        }
    }
    return remain_enemy;
}

void StateBattle::GetItem()
{
    int const rand_num = GetRandToMax(10000); //万分率.
    int total = 0;
    for( int i = 1; i < ItemType_Num; i++ )// ItemType_None は考えないので i = 1 から.
    {
        total += DropPamiriado( static_cast<ItemType>(i) );

        // 取得決定.
        if( rand_num < total ){
            ItemType const get_item = static_cast<ItemType>(i);
            gSaveData.m_item[get_item]++;
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_Decide ) );
            std::string log = NameOf(static_cast<ItemType>(i));
            log+="を手に入れた。";
            m_log_printer->Print(log);
            return;
        }
    }
}

void StateBattle::DrawItem() const
{
    DrawTexture( Vector2(0,0), ImageType_ItemList );
    DrawTexture( Vector2(0,0), ImageType_ItemFrame );
}

void StateBattle::UpdateHiScore()
{
    if( gSaveData.m_max_break < mBreakEnemyCounter->Num() ){
        gSaveData.m_max_break = mBreakEnemyCounter->Num();
    }
}

void StateBattle::InitEnemy()
{
    Enemy::Type type = Enemy::Type_GreenSlime;
	for( int i = 0 ; i < m_stage_info.total_enemy; i++ ){
	    //敵を切り替える場所だったら切り替える.
	    for( int j = 0 ; j < EnemyPointMax ; j++ ){
	        if( m_stage_info.change_point[j] == i ){
	            type = m_stage_info.change_enemy[j];
	        }
	    }
		m_enemy.push_back( boost::shared_ptr<Enemy>(new Enemy( type )) );
        m_enemy[i]->SetPosition( Vector2( i * 100 + 300 , 350 ) );
    }
}

void StateBattle::UpdateDebug()
{
    if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_F12 ) ) )
    {
        m_is_debug_draw = !m_is_debug_draw;
    }
    else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_F11 ) ) )
    {
    	m_manager.ChangeState( ProjectState_Title );
    }
}



