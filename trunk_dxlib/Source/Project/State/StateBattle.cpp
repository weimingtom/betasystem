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
 , m_stage_info( StageInfoOf( StageType_ScoreAttack ) )
 , m_is_debug_draw( false )
{
    m_player_pos.y = 300;
    InitEnemy();
    InitStepDecideMeter();
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
	        //プレイヤーを減らす.
			mPlayerLife->Sub();
	        if( !mPlayerLife->IsEmpty() ){
	            InitStepDecideMeter();
	        }else{
                InitResult();
            }
	    }
        break;
	case Step_Result:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
            UpdateHiScore();
	    	m_manager.ChangeState( ProjectState_Title );
	    }
		break;
    case Step_Clear:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
    	    m_manager.ChangeState( ProjectState_Title );
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
        DrawTexture( Vector2(100,100), ImageType_GameEnd );
        break;
    case Step_Result:
        DrawTexture( Vector2(100,100), ImageType_Result );
        DrawFormatString( 250 , 200 , ColorOf() , "%d匹！", m_stage_info.total_enemy - RemainEnemy() );
        break;
    case Step_Clear:
        DrawFormatString( 250 , 200 , ColorOf() , "ステージクリア！");
        break;
    }
    //mBreakEnemyCounter->Draw();
    //DrawItem();
    //mPlayerLife->Draw();
    
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

/**
	メーターの更新.
*/
void StateBattle::UpdateMeter( int meter_index )
{
	m_gauge[meter_index]->Update();
}

void StateBattle::SetStep( Step step )
{
	m_step = step;
}

void StateBattle::InitStepWaitDash()
{
    SetStep( Step_WaitDash );
    m_frame = 0;
	m_player_power += m_gauge[0]->GetValue();
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
                //GetItem();
                mBreakEnemyCounter->Add();
                gSaveData.m_total_break++;
            }
        }
    }
    //ダッシュ終了.
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
}

/**
    ゲージの描画
*/
void StateBattle::DrawDashGauge() const
{
	for( int i = 0; i < 2 ; i++ ){
	    DrawGauge( 10 , 410 + 25 * i , *m_gauge[i].get() );
	}
}

void StateBattle::DrawGauge( int x, int y, Gauge const& gauge) const
{
	int const height = 20;
	//下地
	DrawBox( x, y, x+gauge.GetMax() , y+height, GetColor( 0,0,0 ), TRUE );
	
	int color = GetColor( 0, 255 / gauge.GetMax() * gauge.GetValue(), 0 );
	DrawBox( x, y, x+gauge.GetValue() , y+height, color, TRUE );
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
}

void StateBattle::InitResult()
{
	SetStep( Step_Result );
	m_player_texture->Set( AnimDataOf( AnimType_PlayerGrave ) );
}

/**
    メーター決定への遷移.
    全て初期化.
*/
void StateBattle::InitStepDecideMeter()
{
    SetStep( Step_DecideMeter );
    m_target_meter = 0;
    m_gauge[0].reset( new Gauge(gSaveData.m_player_hp) );
    m_gauge[1].reset( new Gauge(gSaveData.m_player_mp) );
	m_player_texture->Set( AnimDataOf( AnimType_PlayerIdling ) );
}

/**
    右クリキャンセル時の処理.
*/
void StateBattle::CancelDecideMeter()
{
    m_target_meter = 0;
	m_gauge[0]->SetValue(0);
	m_gauge[1]->SetValue(0);
}

void StateBattle::StepDecideMeter()
{
//    UseItem();
    //やり直し機能.
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) ){
        CancelDecideMeter();
    }
	UpdateMeter( m_target_meter );
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
        PlaySound( *m_gauge[m_target_meter].get() );
        if( m_target_meter >= 1 ){
            InitStepWaitDash();
        }else{
            m_target_meter++;
        }
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

void StateBattle::PlaySound( Gauge const& gauge )
{
    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Decide ) );
}


