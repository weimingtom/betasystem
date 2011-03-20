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

StateBattle::StateBattle( StateManagerBase& manager )
 : m_manager( manager )
 , m_add_meter(0)
 , m_background( new ScrollBackground() )
 , m_player_speed(0.0f)
 , m_frame(0)
 , m_camera( new Camera() )
 , m_player_power(0)
 , m_player_texture( new AnimTexture(
    ImageHandleOf( ImageType_Player ), AnimDataOf( AnimType_PlayerIdling ) ) )
 , m_player_life(1)
 , m_meter_max(100)
 , m_break_num(0)
 , m_special_power_max(5)
 , m_special_power(0)
 , m_special_random(100)
{
    m_player_pos.y = 300;
    for( int i = 0 ; i < EnemyNum; i++ ){
        m_enemy[i].SetPosition( Vector2( i * 100 + 300 , 350 ) );
    }
    InitStepDecideMeter();
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
            InitResult();
	    }
        break;
	case Step_Result:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	        if( m_player_life > 0 ){
	            InitStepDecideMeter();
	        }else{
    	    	m_manager.ChangeState( ProjectState_Title );
            }
	    }
		break;
    case Step_Clear:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
    	    m_manager.ChangeState( ProjectState_Title );
        }
        break;
    case Step_Special:
        m_frame++;
        if( m_frame > 80 ){
            SetStep(Step_Dash);
            m_player_power += 10 * m_special_power * m_special_power;
            m_special_power = 0;
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
    for( int i = 0 ; i < EnemyNum ; i++ ){
		m_enemy[i].Draw( m_camera->Position() );
    }

    switch( m_step )
    {
    case Step_DecideMeter:
        DrawGauge();
		//説明
        DrawTexture( Vector2(100,30), ImageType_Explain );
        break;
    case Step_Dash:
        {
            //電球
            Vector2 pos = m_player_pos - m_camera->Position();
            DrawTexture( pos, ImageType_Light, static_cast<double>(m_special_power), 1.0f );
        }
        break;
	case Step_WaitDash:
        DrawGauge();
        break;
    case Step_DashEnd:
        DrawTexture( Vector2(100,100), ImageType_GameEnd );
        break;
    case Step_Result:
        DrawTexture( Vector2(100,100), ImageType_Result );
        DrawFormatString( 250 , 200 , ColorOf() , "%d匹！", EnemyNum - RemainEnemy() );
        break;
    case Step_Clear:
        DrawFormatString( 250 , 200 , ColorOf() , "ステージクリア！");
        break;
    case Step_Special:
        switch( m_special_power )
        {
        case 0:
        case 1:
        case 2:
    		DrawTexture( Vector2(100-m_frame*1.5,20), ImageType_Cutin );
    		break;
        case 3:
        case 4:
    		DrawTexture( Vector2(100-m_frame*1.5,20), ImageType_Cutin );
    		break;
        default:
    		DrawTexture( Vector2(100-m_frame*1.5,20), ImageType_Cutin );
    		break;
        }
    }
    //プレイヤーパワーの描画.
    DrawFormatString( 0 , 440 , ColorOf() , "power[%d]", m_player_power );
    int const green = Clamp( 0, m_player_power, 255 );
    DrawBox( 0, 460, 0+m_player_power , 460+20, GetColor( 255, green, 0 ), TRUE );
    DrawBreakNum();
    DrawDebug();
}

/**
	メーターの更新.
*/
void StateBattle::UpdateMeter( int meter_index )
{
	m_meter[meter_index] += m_add_meter;
	if( m_meter[meter_index] >= m_meter_max ){
		m_add_meter = -2;
	}
	if( m_meter[meter_index] <= 0){
		m_add_meter = 2;
	}
}

void StateBattle::SetStep( Step step )
{
	m_step = step;
}

void StateBattle::InitStepWaitDash()
{
    SetStep( Step_WaitDash );
    m_frame = 0;
	m_player_power += m_meter[0] + m_meter[1] ;
	if( m_meter[0] == m_meter_max ){
    	m_special_random -= 15;
	}
	if( m_meter[1] == m_meter_max ){
	    m_special_random -= 15;
	}
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
    //必殺技の使用.
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) && m_special_power > 0 ){
        SingletonSoundLoader::Get()->Play( NameOf( SoundType_Special ) );
        m_special_random += 10; //!< ひらめきにくくなっていく.
        m_frame = 0;
        SetStep( Step_Special );
    }

    m_player_speed = 30;
    m_player_pos.x += m_player_speed;
    /**
        プレイヤーと敵がぶつかったら、敵をふっとばす.
    */
    for( int i = 0 ; i < EnemyNum ; i++ ){
        if( m_enemy[i].IsAlive() ){
            if( m_enemy[i].Position().x < m_player_pos.x ){
                m_player_power--;
                SingletonSoundLoader::Get()->Play( NameOf( SoundType_OK ) );
                m_enemy[i].SetSpeed( Vector2( m_player_speed * 2, - GetRand(20) ) );
                m_enemy[i].SetAlive( false );
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
    // 所持アイテムの表示.
    for( int i = 0; i < SaveData::ItemBagSize ; i++ ){
        DrawFormatString( 0 , i*20 , ColorOf() , "[F%dキー]>%s", i+1, NameOf( static_cast<ItemType>(gSaveData.m_item[i]) ) );
    }

    DrawFormatString( 0 , 220 , ColorOf() , "総討伐数[%d]", gSaveData.m_total_break );
    DrawFormatString( 0 , 240 , ColorOf() , "討伐数[%d]", m_break_num );
    DrawFormatString( 0 , 260 , ColorOf() , "必殺技パワー[%d/%d]", m_special_power, m_special_power_max);
    DrawFormatString( 0 , 280 , ColorOf() , "残機[%d]", m_player_life  );

    // 現在地の表示.
    int const width = 300;
    int const x = 300;
    DrawBox( x, 0, x + width , 10, GetColor( 255, 0, 0 ), TRUE );
    DrawBox(
        x + width * ( EnemyNum - RemainEnemy() ) / EnemyNum , 0,
        x + width , 10,
        GetColor( 0, 255, 0), TRUE );
}

/**
    ゲージの描画
*/
void StateBattle::DrawGauge() const
{
	for( int i = 0; i < 2 ; i++ ){
		int const x = 50;
		int const y = 70 * i + 350;
		DrawCircle( x, y, m_meter_max / 3, GetColor( 0,0,0 ), TRUE );
		int color = GetColor( 0, 255 / m_meter_max * m_meter[i], 0);
		if( m_meter[i] == m_meter_max ){ color = GetColor( 255, 255, 0 ); }
		if( i == 0 ){
    		DrawCircle( x, y, m_meter[i] / 3 , color, TRUE );
		}else{
			DrawCircle( x, y, m_meter[i] / 3 , color, TRUE ); 
		}
	}
}

void StateBattle::UpdateCommon()
{
    m_player_texture->Update();
    m_player_texture->Set( m_player_pos );
    //敵更新
    for( int i = 0 ; i < EnemyNum ; i++ ){
        m_enemy[i].Update();
    }
    //カメラはプレイヤー追尾.
	m_camera->SetPosition( m_player_pos - Vector2( 640/2 - 200, 480/2 + 50 ) );
	//背景スクロール
    m_background->SetScroll( m_camera->Position() );
}

void StateBattle::InitResult()
{
	SetStep( Step_Result );

	m_player_texture->Set( AnimDataOf( AnimType_PlayerIdling ) );
    //プレイヤーを減らす.
    m_player_life--;
}

void StateBattle::InitStepDecideMeter()
{
    SetStep( Step_DecideMeter );
    m_target_meter = 0;
    m_meter[0]=0;
    m_meter[1]=0;
}

void StateBattle::StepDecideMeter()
{
    UseItem();
    //やり直し機能.
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) ){
        InitStepDecideMeter();
    }
	UpdateMeter( m_target_meter );
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
        if( m_meter[m_target_meter] == m_meter_max ){
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
				switch( gSaveData.m_item[i] ){
                case ItemType_Meet:
                    m_meter_max += 10;
                    break;
                case ItemType_Water:
                    m_player_power += 10;
                    break;
                }
                SingletonSoundLoader::Get()->Play( NameOf( SoundType_Item ) );
                gSaveData.m_item[i] = ItemType_None;
            }
        }
    }
}

int StateBattle::RemainEnemy() const
{
    int remain_enemy = 0;
    for( int i = 0 ; i < EnemyNum ; i++ ){
        if( m_enemy[i].IsAlive() ){
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
    // まだ適当な確率.
    if( GetRandToMax(30) == 0 ){
        //取得するアイテムの決定.
        ItemType const type = static_cast<ItemType>( GetRandToMax(ItemType_Num-1) + 1); // Noneが出ないように小細工.
        //空いてる場所に詰め込む
        for( int i = 0 ; i < SaveData::ItemBagSize ; i++ ){
            if( gSaveData.m_item[i] == ItemType_None ){
                gSaveData.m_item[i] = type;
                SingletonSoundLoader::Get()->Play( NameOf( SoundType_Item ) );
                return;
            }
        }
    }
}

