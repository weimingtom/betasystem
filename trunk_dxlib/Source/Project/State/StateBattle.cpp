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
#include "Project/Singleton/Keyboard.hpp"
#include "Project/Draw.hpp"
#include "Project/ScrollBackground.hpp"
#include "Project/AnimData.hpp"
#include "Project/SaveData.hpp"
#include <math.h>
#include "Gauge.hpp"

namespace {
    int const MeterDefault = 100;
    int const CriticalRangeDefault = 1;
} // namespace unnamed

StateBattle::StateBattle( StateManagerBase& manager )
 : m_manager( manager )
 , m_background( new ScrollBackground() )
 , m_frame(0)
 , m_camera( new Camera() )
 , m_player_power(0)
 , m_player_texture( new AnimTexture(
    ImageHandleOf( ImageType_Player ), AnimDataOf( AnimType_PlayerIdling ) ) )
 , m_player_life(1)
 , m_break_num(0)
 , m_special_power_max(5)
 , m_special_random(100)
 , m_stage_info( StageInfoOf( StageType_ScoreAttack ) )
{
    m_player_pos.y = 300;
    InitEnemy();
    InitStepDecideMeter();
}

StateBattle::~StateBattle()
{
    for( int i = 0 ; i < m_stage_info.total_enemy; i++ ){
        delete m_enemy[i];
    }
}

void StateBattle::Update()
{
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
            m_player_life--;
	        if( m_player_life > 0 ){
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
    case Step_Special:
    	StepSpecial();
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
		m_enemy[i]->Draw( m_camera->Position() );
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
    case Step_Special:
    	DrawStepSpecial();
    }
    DrawBreakNum();
    DrawItem();
    DrawFace();
    DrawSword();
    DrawDebug();
}

/**
	メーターの更新.
*/
void StateBattle::UpdateMeter( int meter_index )
{
	m_gauge[meter_index].Update();
}

void StateBattle::SetStep( Step step )
{
	m_step = step;
}

void StateBattle::InitStepWaitDash()
{
    SetStep( Step_WaitDash );
    m_frame = 0;
	m_player_power += m_gauge[0].GetValue() + m_gauge[1].GetValue();
	if( m_gauge[0].IsCritical() ){
    	m_special_random -= 15;
	}
	if( m_gauge[1].IsCritical() ){
	    m_special_random -= 15;
	}
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

void StateBattle::InitStepSpecial()
{
    SetStep( Step_Special );
    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Special ) );
    m_frame = 0;
    m_gauge_special = Gauge();
}

void StateBattle::StepSpecial()
{
	m_gauge_special.Update();
	//クリックした.
	if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
		//サウンド再生とかする予定.
		
		//ゲージを確定させる.
		m_gauge_special.SetPause(true);
	}
	//特定の時間経過で、自動的に次へ進む.
    m_frame++;
    if( m_frame > 100 ){
		m_gauge_special.SetPause(true);
		m_player_power += 10 * m_special_power * m_special_power;
		m_special_power = 0;
		if( !m_gauge_special.IsCritical() ){
			m_special_random += 10; //!< クリティカルでないと、ひらめきにくくなる.
		}
        SetStep(Step_Dash);
    }
}

void StateBattle::StepDash()
{
    //必殺技の使用.
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) && m_special_power > 0 ){
    	InitStepSpecial();
    	return;
    }

    float player_speed = 30.0f;
    if( m_player_power > 70 ){
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
                GetItem();
                // 必殺
                if( GetRandToMax(m_special_random) == 0 ){
                    m_special_power++;
                    if( m_special_power > m_special_power_max ){
                        m_special_power = m_special_power_max;
                    }
                    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Just ) );
                }
                //討伐カウント.
                m_break_num++;
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
}

/**
    ゲージの描画
*/
void StateBattle::DrawDashGauge() const
{
	for( int i = 0; i < 2 ; i++ ){
		int const x = 10;
		int const y = 430 + 25 * i ;
		int const height = 20;
		//下地
		DrawBox( x, y, x+m_gauge[i].GetMax() , y+height, GetColor( 255,0,0 ), TRUE );
		DrawBox( x, y, x+m_gauge[i].GetMax()-m_gauge[i].GetCritical(), y+height, GetColor( 0,0,0 ), TRUE );
		
		int color = GetColor( 0, 255 / m_gauge[i].GetMax() * m_gauge[i].GetValue(), 0 );
		if( Range( m_gauge[i].GetMax()-m_gauge[i].GetCritical(), m_gauge[i].GetValue(), m_gauge[i].GetMax() ) ){
		    color = GetColor( 255, 255, 0 );
        }
		DrawBox( x, y, x+m_gauge[i].GetValue() , y+height, color, TRUE );
	}
}

/**
	必殺技時の描画.
*/
void StateBattle::DrawStepSpecial() const
{
	// カットイン画像.
	DrawTexture( Vector2(100-m_frame*1.5,20), ImageType_Cutin );

	int const x = 10;
	int const y = 430 + 25;
	int const height = 20;
	//下地
	DrawBox( x, y, x+m_gauge_special.GetMax() , y+height, GetColor( 255,0,0 ), TRUE );
	DrawBox( x, y, x+m_gauge_special.GetMax()-m_gauge_special.GetCritical(), y+height, GetColor( 0,0,0 ), TRUE );
	
	int color = GetColor( 0, 255 / m_gauge_special.GetMax() * m_gauge_special.GetValue(), 0 );
	if( Range( m_gauge_special.GetMax()-m_gauge_special.GetCritical(), m_gauge_special.GetValue(), m_gauge_special.GetMax() ) ){
	    color = GetColor( 255, 255, 0 );
    }
	DrawBox( x, y, x+m_gauge_special.GetValue() , y+height, color, TRUE );
}

void StateBattle::UpdateCommon()
{
    m_player_texture->Update();
    m_player_texture->Set( m_player_pos );
    //敵更新
    for( int i = 0 ; i < m_stage_info.total_enemy ; i++ ){
        m_enemy[i]->Update();
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
    m_gauge[0] = Gauge();
    m_gauge[1] = Gauge();
	m_player_texture->Set( AnimDataOf( AnimType_PlayerIdling ) );
    m_critical_range = CriticalRangeDefault;
    m_special_power = 0;
}

/**
    右クリキャンセル時の処理.
*/
void StateBattle::CancelDecideMeter()
{
    m_target_meter = 0;
	m_gauge[0].SetValue(0);
	m_gauge[1].SetValue(0);
}

void StateBattle::StepDecideMeter()
{
    UseItem();
    //やり直し機能.
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) ){
        CancelDecideMeter();
    }
	UpdateMeter( m_target_meter );
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
		if( m_gauge[m_target_meter].IsCritical() ){
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_Just ) );
        }else{
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_Decide ) );
        }
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
        if( KeyInput()->IsTrig( static_cast<KeyboardInput::Type>( KeyboardInput::Type_F1 + i ) ) )
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
	switch( type ){
    case ItemType_Meet:
		m_gauge[0].SetCritical( m_gauge[0].GetCritical() + 4 );
		m_gauge[1].SetCritical( m_gauge[1].GetCritical() + 4 );
        break;
    case ItemType_GoodMeet:
		m_gauge[0].SetCritical( m_gauge[0].GetCritical() + 10 );
		m_gauge[1].SetCritical( m_gauge[1].GetCritical() + 10 );
        break;
    case ItemType_LifeWater:
        m_player_life++;
        break;
    case ItemType_CriticalGrass:
        m_critical_range+=2;
        break;
    }
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

/**
    指定した桁の数字を取得する.
    @param num 操作対象の数値.
    @param digit 取得したい桁. １桁目ならば１、２桁目ならば２.
*/
int StateBattle::DigitOf(int num,int digit) const
{
    double const d_digit = static_cast<double>(digit);
    double const Ten = 10.0f;

    double const result = num % static_cast<int>( pow( Ten, d_digit ) );
    return static_cast<int>( result / pow(Ten,d_digit-1.0f) );
}

void StateBattle::DrawBreakNum() const
{
    int const width = 50;
    int const height = 100;
    int max_digit = 5;
    
    /*
        上の桁の有無によって、表示非表示を決定する.
        その桁が０で、且つ上位桁が全て０ならば表示しない.
    */
    for(int i = 1 ; i < max_digit ; i++ ){
        if( DigitOf(m_break_num,i) == 0 ){
            int total = 0;
            for( int j = i + 1 ; j < max_digit ; j++ ){
                total += DigitOf(m_break_num,j);
            }
            if( total == 0 ){ continue; }
        }
        
        DrawRectGraph(
            600 - i*width, 30,
            0 + width * DigitOf(m_break_num,i), 0,
            width, height,
            ImageHandleOf(ImageType_Number), TRUE, FALSE );
    }
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
                    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Item ) );
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

void StateBattle::DrawFace() const
{
    int x = 0;
    int y = 50;
    int width = 70;
    DrawTexture( Vector2(x,y) , ImageType_FaceFrame );
    x+=width;
    for( int i = 0 ; i < m_player_life ; i++ ){
        DrawTexture( Vector2(x+i*width,y) , ImageType_Face );
    }
}

void StateBattle::DrawSword() const
{
    int x = 0;
    int y = 120;
    DrawTexture( Vector2(x,y) , ImageType_SwordFrame );
    
    int const sword_of_hand = 40;
    int width = 150;
    DrawRectGraph(
        x,y,
        0,0,
        40 + (width - sword_of_hand)/ m_special_power_max * m_special_power,
        75,
        ImageHandleOf(ImageType_SwordPower), TRUE, FALSE );

    
}

void StateBattle::UpdateHiScore()
{
    if( gSaveData.m_max_break < m_break_num ){
        gSaveData.m_max_break = m_break_num;
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
        m_enemy.push_back( new Enemy( type ) );
        m_enemy[i]->SetPosition( Vector2( i * 100 + 300 , 350 ) );
    }
}

