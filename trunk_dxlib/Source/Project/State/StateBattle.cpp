#include "StateBattle.hpp"

#include "System/StateManagerBase.hpp"
#include "System/Camera.hpp"
#include "System/Range.hpp"
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
 , m_player_power(0)
 , m_player_texture( new AnimTexture(
    ImageHandleOf( ImageType_Player ), AnimDataOf( AnimType_PlayerIdling ) ) )
 , mPlayerLife( new PlayerLife(1) )
 , mBreakEnemyCounter( new BreakEnemyCounter() )
 , m_stage_info( StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) ) )
 , m_is_debug_draw( false )
 , m_msg_printer( new MsgPrinter() )
{
    m_player_pos.y = 300;
    InitEnemy();
    InitPreTalk();
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
	        InitStepDecideMeter();
	    }
	    break;
	case Step_DecideMeter:
	    StepDecideMeter();
	    break;
    case Step_WaitDash:
        StepWaitDash();
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
    	    m_manager.ChangeState( ProjectState_SelectStage );
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
        if( m_enemy[i]->IsAlive() ){
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
    //DrawItem();
    //mPlayerLife->Draw();
	m_msg_printer->Draw();
    
	{
		//HP表示.
		int x = 10,y = 460;
		int width = gSaveData.m_player_hp;
		int height = 20;
		DrawBox( x, y, x+width , y+height, GetColor( 0,0,0 ), TRUE );
		DrawBox( x, y, x+m_player_power , y+height, GetColor( 0,255,0 ), TRUE );
	}

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
	m_player_power += m_gauge->GetValue();
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

void StateBattle::StepDash()
{
    float player_speed = 30.0f;
    if( m_player_power > 300 ){
        player_speed = 50.0f;
    }
    else if( m_player_power > 70 ){
        player_speed = 30.0f;
    }
    else if( m_player_power > 20 ){
        player_speed = 20.0f;
    }
    else{
        player_speed = 10.0f;
    }
    
    if( SingletonInputMouse::Get()->IsHold( InputMouse::Type_Right ) ){
        player_speed *= 1.5;
    }
    m_player_pos.x += player_speed;
    /**
        プレイヤーと敵がぶつかったら、敵をふっとばす.
    */
    for( int i = 0 ; i < m_stage_info.total_enemy ; i++ ){
        if( m_enemy[i]->IsAlive() ){
            if( m_enemy[i]->Position().x < m_player_pos.x ){
                m_player_power -= m_enemy[i]->GetHP();
                SingletonSoundLoader::Get()->Play( NameOf( SoundType_OK ) );
                m_enemy[i]->SetSpeed( Vector2( player_speed * 2, - GetRand(20) ) );
                m_enemy[i]->SetAlive( false );
                mBreakEnemyCounter->Add();
                gSaveData.m_total_break++;
                gSaveData.m_player_exp += m_enemy[i]->GetExp();
            }
        }
    }
    //レベルアップ判定.
    {
        if(gSaveData.m_player_exp > gSaveData.m_player_level*10){
            gSaveData.m_player_exp -= gSaveData.m_player_level*10;
            gSaveData.m_player_level++;
            gSaveData.m_player_hp+=10;
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_Just ) );
        }
    }
    
    //ゲームオーバー判定.
	if( m_player_power <= 0 ){
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
    DrawFormatString( x , y+=20,    ColorOf() , "max_hp[%d]", gSaveData.m_player_hp);
    DrawFormatString( x , y+=20,    ColorOf() , "max_mp[%d]", gSaveData.m_player_mp);
    DrawFormatString( x , y+=20,    ColorOf() , "hp[%d]", m_player_power);
    DrawFormatString( x , y+=20,    ColorOf() , "m_player_exp[%d]", gSaveData.m_player_exp);
    DrawFormatString( x , y+=20,    ColorOf() , "m_player_level[%d]", gSaveData.m_player_level);
    StageInfo const info = StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) );
    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "stage_name[%s]", info.name);
    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "total_enemy[%d]", info.total_enemy);
    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "break_enemy[%d]", mBreakEnemyCounter->Num() );
    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "進行度[%f]", (float)mBreakEnemyCounter->Num()/info.total_enemy );
}

/**
    ゲージの描画
*/
void StateBattle::DrawDashGauge() const
{
	for( int i = 0; i < 2 ; i++ ){
	    DrawGauge( 10 , 410 + 25 * i );
	}
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
        if( m_enemy[i]->IsAlive() ){
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
    m_gauge.reset( new Gauge(gSaveData.m_player_hp) );
	m_player_texture->Set( AnimDataOf( AnimType_PlayerIdling ) );
}

void StateBattle::StepDecideMeter()
{
	m_gauge->Update(SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ));

	if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
		//連打音.
	    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Decide ) );
	}

	if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) )
    {
        SingletonSoundLoader::Get()->Play( NameOf( SoundType_Decide ) );
        InitStepWaitDash();
    }
}

/**
    アイテムの使用.
*/
void StateBattle::UseItem()
{
    for( int i = 0 ; i < SaveData::ItemBagSize ; i++ ){
        if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_F1 + i ) ) )
        {
            if( gSaveData.m_item[i] != ItemType_None ){
                UseItem( static_cast<ItemType>( gSaveData.m_item[i] ) );
                gSaveData.m_item[i] = ItemType_None;
            }
        }
    }
}

void StateBattle::UseItem( ItemType type )
{
/*
	switch( type ){
    case ItemType_Meet:
		m_gauge[0]->SetMax( m_gauge[0]->GetMax() + 4 );
		m_gauge[1]->SetMax( m_gauge[1]->GetMax() + 4 );
        break;
    case ItemType_GoodMeet:
		m_gauge[0]->SetMax( m_gauge[0]->GetMax() + 10 );
		m_gauge[1]->SetMax( m_gauge[1]->GetMax() + 10 );
        break;
    case ItemType_LifeWater:
    	mPlayerLife->Add();
        break;
    }
    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Item ) );
*/
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
            for( int j = 0 ; j < SaveData::ItemBagSize ; j++ ){
                if( gSaveData.m_item[j] == ItemType_None ){
                    gSaveData.m_item[j] = static_cast<ItemType>(i);
                    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Decide ) );
                    return;
                }
            }
            return;
        }
    }
}

void StateBattle::DrawItem() const
{
    int const width = 50;
	int const height = 50;
    for(int i = 0 ; i < SaveData::ItemBagSize ; i++ ){
        DrawRectGraph(
            i*width, 0,
            gSaveData.m_item[i] * width , 0,
            width, height,
            ImageHandleOf(ImageType_ItemList), TRUE, FALSE );
    }
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



