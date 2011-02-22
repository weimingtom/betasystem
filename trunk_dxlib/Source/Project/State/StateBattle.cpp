#include "StateBattle.hpp"

#include "System/StateManagerBase.hpp"
#include "System/Camera.hpp"
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
    //プレイヤーパワーの描画.
    DrawBox( 0, 420, 0+m_player_power , 420+20, GetColor( 255, 0, 0 ), TRUE );

    switch( m_step )
    {
    case Step_DecideMeter:
        DrawGauge();
		//説明
        DrawTexture( Vector2(200,30), ImageType_Explain );
        break;
	case Step_WaitDash:
        DrawGauge();
		//カットインの描画.
		DrawTexture( Vector2(100,100), ImageType_Cutin );
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
    }
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
	m_player_power = m_meter[0] + m_meter[1] ;
}

void StateBattle::StepWaitDash()
{
    m_frame++;
    if( m_frame > 100 ){
        //InitStepDash
        m_player_texture->Set( AnimDataOf( AnimType_PlayerDash ) );
        SetStep( Step_Dash );
    }
}

void StateBattle::StepDash()
{
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
        m_player_power++;
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
                // アイテム取得、今は適当な確率
                if( GetRandToMax(30) == 0 ){
                    ItemType const type = static_cast<ItemType>( GetRandToMax(ItemType_Num) );
                    gSaveData.m_item[type]++;
                }
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
    DrawFormatString( 0 , 0 , ColorOf() , "m_player_pos[%f,%f]", m_player_pos.x , m_player_pos.y );
    DrawFormatString( 0 , 10 , ColorOf() , "m_player_speed[%f]", m_player_speed );
    DrawFormatString( 0 , 20 , ColorOf() , "m_meter1[%d]", m_meter[0] );
    DrawFormatString( 0 , 30 , ColorOf() , "m_meter2[%d]", m_meter[1] );

    DrawFormatString( 0 , 200 , ColorOf() , "残機[%d]", m_player_life  );
    // 所持アイテムの表示.
    DrawFormatString( 0 , 210 , ColorOf() , "所持アイテム." );
    for( int i = 0; i < ItemType_Num ; i++ ){
        DrawFormatString( 0 , 220 + i*10 , ColorOf() , "%s[%d個]", NameOf( static_cast<ItemType>(i) ) , gSaveData.m_item[i] );
    }
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
		int const y = 70 * i + 300;
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
    UseItem();
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
    if( KeyInput()->IsTrig( KeyboardInput::Type_1 ) )
    {
        if( gSaveData.m_item[0] > 0 ){
            gSaveData.m_item[0]--;
            m_meter_max += 10;
        }
    }
    if( KeyInput()->IsTrig( KeyboardInput::Type_2 ) )
    {
        if( gSaveData.m_item[1] > 0 ){
            gSaveData.m_item[1]--;
            m_player_power += 10;
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

