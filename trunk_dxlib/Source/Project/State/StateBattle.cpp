#include "StateBattle.hpp"

#include "System/StateManagerBase.hpp"
#include "System/Camera.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "DxLibWrapper/Random.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Draw.hpp"
#include "Project/ScrollBackground.hpp"

static int const meter_max = 100;


StateBattle::StateBattle( StateManagerBase& manager )
 : m_manager( manager )
 , m_add_meter(0)
 , m_step( Step_DecideMeter1 )
 , m_background( new ScrollBackground() )
 , m_player_speed(0.0f)
 , m_frame(0)
 , m_camera( new Camera() )
 , m_player_power(0)
{
    m_player_pos.y = 300;
    m_meter[0]=0;
    m_meter[1]=0;
    
    for( int i = 0 ; i < EnemyNum; i++ ){
        m_enemy[i].SetPosition( Vector2( i * 100 + 300 , 350 ) );
    }
}

void StateBattle::Update()
{
    for( int i = 0 ; i < EnemyNum ; i++ ){
        m_enemy[i].Update();
    }

    //カメラはプレイヤー追尾.
	m_camera->SetPosition( m_player_pos - Vector2( 640/2 - 200, 480/2 + 50 ) );
	
	//背景スクロール
    m_background->SetScroll( m_camera->Position() );
    
	switch( m_step )
	{
	case Step_DecideMeter1:
		UpdateMeter(0);
        if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
        {
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_Decide ) );
            SetStep( Step_DecideMeter2 );
        }
		break;
	case Step_DecideMeter2:
        //やり直し機能.
        if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) )
        {
            m_manager.ChangeState( ProjectState_Battle );
        }
		UpdateMeter(1);
		DecideMeter();
	    break;
    case Step_WaitDash:
        StepWaitDash();
        break;
	case Step_Dash:
		DashPlayer();
		break;
    case Step_DashEnd:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	    	SetStep( Step_Result );
	    }
        break;
	case Step_Result:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	    	m_manager.ChangeState( ProjectState_Title );
	    }
		break;
	}
}

void StateBattle::Draw() const
{
    DrawBox( 0, 0, 640 , 480, GetColor( 200,222,200 ), TRUE );
    
    m_background->Draw( m_camera->Position() );
	DrawTexture( m_player_pos - m_camera->Position(), ImageType_Player );

	//敵の描画.
    for( int i = 0 ; i < EnemyNum ; i++ ){
		m_enemy[i].Draw( m_camera->Position() );
    }
    
    switch( m_step )
    {
    case Step_DecideMeter1:
    case Step_DecideMeter2:
		//説明
        DrawTexture( Vector2(250,30), ImageType_Explain );
	case Step_WaitDash:
		//ゲージの描画
		for( int i = 0; i < 2 ; i++ ){
    		int const x = 50;
    		int const y = 80 * i + 100;
    		DrawCircle( x, y, meter_max / 3, GetColor( 0,0,0 ), TRUE );

    		int color = GetColor( 0, 255 / meter_max * m_meter[i], 0);
    		if( m_meter[i] > 98 ){ color = GetColor( 255, 255, 0 ); }
    		if( i == 0 ){
        		DrawCircle( x, y, m_meter[i] / 3 , color, TRUE );
			}else{
    			DrawCircle( x, y, m_meter[i] / 3 , color, TRUE ); 
			}
		}
        break;
    case Step_DashEnd:
        DrawTexture( Vector2(100,100), ImageType_GameEnd );
        break;
    case Step_Result:
        DrawTexture( Vector2(100,100), ImageType_Result );
        {
            int break_enemy = 0;
            for( int i = 0 ; i < EnemyNum ; i++ ){
                if( !m_enemy[i].IsAlive() ){
                    break_enemy++;
                }else{
                    break;
                }
            }
            DrawFormatString( 250 , 200 , ColorOf() , "%d匹！", break_enemy );
        }
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
	if( m_meter[meter_index] >= meter_max ){
		m_add_meter = -2;
	}
	if( m_meter[meter_index] <= 0){
		m_add_meter = 2;
	}
}
/**
	メーターの数値の決定.
*/
void StateBattle::DecideMeter()
{
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
        SingletonSoundLoader::Get()->Play( NameOf( SoundType_Decide ) );
    	m_player_power = m_meter[0] + m_meter[1];
    	SetStep( Step_WaitDash );
    }
}

void StateBattle::SetStep( Step step )
{
	m_step = step;
}

void StateBattle::StepWaitDash()
{
    m_frame++;
    if( m_frame > 100 ){
        SetStep( Step_Dash );
    }
}

void StateBattle::DashPlayer()
{
    m_player_speed = 25;
    if( m_player_power < 100 ){
        m_player_speed = 20;
    }
    if( m_player_power < 30 ){
        m_player_speed = 10;
    }
    if( m_player_power < 20 ){
        m_player_speed = 5;
    }
    m_player_pos.x += m_player_speed;

    /**
        プレイヤーと敵がぶつかったら、敵をふっとばす.
    */
    for( int i = 0 ; i < EnemyNum ; i++ ){
        if( m_enemy[i].IsAlive() ){
            if( m_enemy[i].Position().x < m_player_pos.x ){
                m_player_power--;
                SingletonSoundLoader::Get()->Play( NameOf( SoundType_OK2 ) );
                m_enemy[i].SetSpeed( Vector2( m_player_speed * 2, - GetRand(10) ) );
                m_enemy[i].SetAlive( false );
            }
        }
    }
    
    //ダッシュ終了.
	if( m_player_power <= 0 ){
		SetStep( Step_DashEnd );
	}
}

/**
    デバッグ情報描画.
*/
void StateBattle::DrawDebug() const
{
    DrawFormatString( 0 , 0 , ColorOf() , "m_player_pos[%f,%f]", m_player_pos.x , m_player_pos.y );
    DrawFormatString( 0 , 10 , ColorOf() , "m_player_speed[%f]", m_player_speed );
}

