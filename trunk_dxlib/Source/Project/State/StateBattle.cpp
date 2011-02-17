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
    //直ぐリセットできるように
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) )
    {
        m_manager.ChangeState( ProjectState_Battle );
    }

    //カメラはプレイヤー追尾.
	m_camera->SetPosition( m_player_pos - Vector2( 640/2 - 200, 480/2 + 50 ) );
	
	//背景スクロール
    m_background->SetScroll( m_camera->Position() );
    
    /**
        プレイヤーと敵がぶつかったら、敵をふっとばす.
    */
    for( int i = 0 ; i < EnemyNum ; i++ ){
        m_enemy[i].Update();
        if( m_enemy[i].IsAlive() ){
            if( m_enemy[i].Position().x < m_player_pos.x ){
                SingletonSoundLoader::Get()->Play( NameOf( SoundType_OK2 ) );
                m_enemy[i].SetSpeed( Vector2( m_player_speed * 2, - GetRand(10) ) );
                m_enemy[i].SetAlive( false );
            }
        }
    }
    
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
	int const x = 100;
	
	for( int i = 0; i < 2 ; i++ ){
    	int const y = 80 * i + 100;
    	DrawCircle( x, y, meter_max / 3, GetColor( 0,0,0 ), TRUE );
    	if( i == 0 ){
        	DrawCircle( x, y, m_meter[i] / 3 , GetColor( 0, 255 / meter_max * m_meter[i], 0), TRUE );
        }else{
    	    DrawCircle( x, y, m_meter[i] / 3 , GetColor( 255 / meter_max * m_meter[i], 0,0), TRUE ); 
        }
    }
    for( int i = 0 ; i < EnemyNum ; i++ ){
		m_enemy[i].Draw( m_camera->Position() );
    }
    
    switch( m_step )
    {
    case Step_DecideMeter1:
    case Step_DecideMeter2:
        DrawTexture( Vector2(100,100), ImageType_Explain );
        break;
    case Step_DashEnd:
        DrawTexture( Vector2(100,100), ImageType_GameEnd );
        break;
    case Step_Result:
        DrawTexture( Vector2(100,100), ImageType_Result );
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
    	m_add_meter = 0;
    	m_player_speed = static_cast<float>( m_meter[0] + m_meter[1] ) / 10; //!< 初速の決定.
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
    // 推進力減退処理.
    if( m_player_speed > 5.5f ){
        m_player_speed *= 0.999f;
    }
    else if( m_player_speed > 2.0f ){
    	m_player_speed *= 0.995f;
    }
    else if( m_player_speed > 1.0f ){
    	m_player_speed *= 0.99f;
    }else{
        m_player_speed *= 0.9f;
    }
	m_player_pos.x += m_player_speed;
	if( m_player_speed < 0.01f ){
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
    {
        int break_enemy = 0;
        for( int i = 0 ; i < EnemyNum ; i++ ){
            if( !m_enemy[i].IsAlive() ){
                break_enemy++;
            }else{
                break;
            }
        }
        DrawFormatString( 300 , 200 , ColorOf() , "[%d]", break_enemy );
    }
}

