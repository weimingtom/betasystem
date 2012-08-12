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
    m_player_pos.x = 0;
    m_player_pos.y = 300;
//    InitEnemy();
    InitPreTalk();
//    SetStep( Step_Dash );
}

StateBattle::~StateBattle()
{
}

void StateBattle::StepBattlePlayer()
{
    if( m_enemy.get() ){
	    m_enemy->Update();
    }
    
    //攻撃.
    if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_1 ) ) ){
        //普通に攻撃.
        m_enemy->SetHP( m_enemy->GetHP() - gSaveData.m_player_attack );
        SetStep(Step_Battle_Enemy);
    }
    //魔法.
    else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_2 ) ) ){
        //MP足りてるなら大ダメージ.
        if( gSaveData.m_player_mp >= 3 ){
            gSaveData.m_player_mp -= 3;
            m_enemy->SetHP( m_enemy->GetHP() - gSaveData.m_player_attack*2 );
            SetStep( Step_Battle_Enemy );
        }
    }
    //回復.
    else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_3 ) ) ){
        //アイテム持ってるなら回復.
        if( gSaveData.m_player_mp >= 3 ){
            gSaveData.m_player_mp -= 3;
            gSaveData.m_player_hp += 30;
            gSaveData.m_player_hp = Clamp(0,gSaveData.m_player_hp, gSaveData.m_player_max_hp);
            SetStep( Step_Battle_Enemy );
        }
    }
    //捕獲.
    else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_4 ) ) ){
        if( GetRandToMax(3) == 0 ){
	        SetStep(Step_Dash);
        }else{
            SetStep(Step_Battle_Enemy);
        }
    }
    //逃げる.
    else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_5 ) ) ){
        if( GetRandToMax(3) == 0 ){
	        SetStep(Step_Dash);
        }else{
            SetStep(Step_Battle_Enemy);
        }
    }
    
    //敵の死亡判定.
    if( m_enemy->GetHP() <= 0 ){
        SetStep(Step_Dash);
    }
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
	case Step_Result:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
            gSaveData.Reset(); // セーブデータ消去.
	    	m_manager.ChangeState( ProjectState_Title );
	    }
		break;
    case Step_Clear:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	        if( gSaveData.m_selected_stage < StageType_Num ){
    	        gSaveData.m_selected_stage++;
            }
    	    m_manager.ChangeState( ProjectState_SelectStage );
        }
        break;
	case Step_Battle_Player:
	    StepBattlePlayer();
        break;
    case Step_Battle_Enemy:
        //敵の攻撃
        gSaveData.m_player_hp -= m_enemy->GetAttack();
        //プレイヤー死亡判定.
        if(gSaveData.m_player_hp <= 0){
    	    m_manager.ChangeState( ProjectState_Title );
	    }else{
            //プレイヤーターンに戻す.
            SetStep(Step_Battle_Player);
        }
        break;
    case Step_OpenGate:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	        SetStep(Step_Dash);
	    }
	    else if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) ){
            gSaveData.m_selected_stage = GetRandToMax( StageType_Num );
            m_manager.ChangeState( ProjectState_Battle );
	    }
        break;
    case Step_TreasureBox:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	        SetStep(Step_Dash);
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

    switch( m_step )
    {
    case Step_DecideMeter:
		//説明
        DrawTexture( Vector2(120,100), ImageType_Explain );
        break;
    case Step_Dash:
        break;
	case Step_WaitDash:
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
    case Step_Battle_Player:
    case Step_Battle_Enemy:
        {
            DrawFormatString( 0 , 0 , ColorOf() , "1:攻撃,2:魔法,3:回復,4:捕獲,5:逃げる");
            DrawFormatString( 250 , 200 , ColorOf() , "戦闘中!");
            DrawFormatString( 250 , 220 , ColorOf() , "EnemyHp[%d]",m_enemy->GetHP());
            if( m_enemy.get() ){
                Vector2 pos(400,300);
                m_enemy->SetPosition(pos);
                Vector2 const dummy;
                m_enemy->Draw(dummy);
            }
        }
        break;
    case Step_OpenGate:
        DrawFormatString( 250 , 200 , ColorOf() , "扉発見!");
        break;
    case Step_TreasureBox:
        DrawFormatString( 250 , 200 , ColorOf() , "宝箱発見!");
        break;
    }
    //mBreakEnemyCounter->Draw();
    //DrawItem();
    //mPlayerLife->Draw();
	m_msg_printer->Draw();

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
//    UseItem();

    if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_F11 ) ) ){
        m_manager.ChangeState( ProjectState_SelectStage );
    }
    //クリックしたら進む
    else if( SingletonInputMouse::Get()->IsHold( InputMouse::Type_Left ) ){
        m_player_pos.x += 5.0f;
        if( KeyInput()->IsHold( static_cast<InputKey::Type>( InputKey::Type_LeftControl ) ) ){
            m_player_pos.x += 10.0f;
        }
        
        //エンカウント判定.
        int const rand_num = GetRandToMax(300);
        if( rand_num == 0 ){
            //戦闘準備して、戦闘遷移へ
            SetStep(Step_Battle_Player);
            
            //今はランダムで敵を決定.
            int const rand_num = GetRandToMax( Enemy::Type_Num );
            m_enemy.reset( new Enemy( static_cast<Enemy::Type>(rand_num) ) );
            
        }else if( rand_num==1 ){
            //扉
            SetStep(Step_OpenGate);
        }else if( rand_num == 2 ){
            //宝箱
            SetStep(Step_TreasureBox);
        }else{
            //最終地点到達.
            StageInfo const info = StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) );
            if( m_player_pos.x > info.total_enemy ){
                //仮で飛ばす.
                //本当はボス戦とかあるんじゃないかな
				gSaveData.m_selected_stage = GetRandToMax( StageType_Num );
				m_manager.ChangeState( ProjectState_Battle );
            }
        }
    }
    else if( SingletonInputMouse::Get()->IsHold( InputMouse::Type_Right ) ){
        //休憩.
        gSaveData.m_player_hp = gSaveData.m_player_max_hp;
    }
}

/**
    デバッグ情報描画.
*/
void StateBattle::DrawDebug() const
{
    //hp
    int const x = 0;
    int y = 100;
    DrawFormatString( x , y+=20,    ColorOf() , "hp[%d/%d]", gSaveData.m_player_hp, gSaveData.m_player_max_hp);
    DrawFormatString( x , y+=20,    ColorOf() , "mp[%d/%d]", gSaveData.m_player_mp, gSaveData.m_player_max_mp);
	y+=20;
	int width = gSaveData.m_player_max_hp;
	int height = 20;
	DrawBox( x, y, x+width , y+height, GetColor( 0,0,0 ), TRUE );
	DrawBox( x, y, x+gSaveData.m_player_hp , y+height, GetColor( 0,255,0 ), TRUE );

    DrawFormatString( x , y+=20,    ColorOf() , "m_player_x[%f]", m_player_pos.x);
    DrawFormatString( x , y+=20,    ColorOf() , "m_player_exp[%d]", gSaveData.m_player_exp);
    DrawFormatString( x , y+=20,    ColorOf() , "m_player_level[%d]", gSaveData.m_player_level);
    StageInfo const info = StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) );
    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "stage_name[%s]", info.name);

    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "進行度");
    {
        float width = 200.0f;
    	int height = 20;
    	DrawBox( x , y+=20, static_cast<int>(x+width) , y+height, GetColor( 0,255,0 ), TRUE );
    	DrawBox( x , y, static_cast<int>(x+width*(float)m_player_pos.x/info.total_enemy) , y+height, GetColor( 255,0,0 ), TRUE );
    }
}

void StateBattle::UpdateCommon()
{
    m_player_texture->Update();
    m_player_texture->Set( m_player_pos );
    //敵更新
/*
    for( int i = 0 ; i < m_stage_info.total_enemy ; i++ ){
        if( m_enemy[i]->IsVisible() ){
            m_enemy[i]->Update();
        }
    }
*/
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
	m_player_texture->Set( AnimDataOf( AnimType_PlayerIdling ) );
}

void StateBattle::StepDecideMeter()
{
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
        gSaveData.m_player_hp += 50;
        break;
    case ItemType_GoodMeet:
        gSaveData.m_player_hp += 20;
        break;
    case ItemType_LifeWater:
        gSaveData.m_player_max_hp += 10;
        break;
    }
    gSaveData.m_player_hp = Clamp(0,gSaveData.m_player_hp,gSaveData.m_player_max_hp);
    
    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Item ) );
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

void StateBattle::UpdateDebug()
{
}



