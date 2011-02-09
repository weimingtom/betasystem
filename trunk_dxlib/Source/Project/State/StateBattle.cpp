#include "StateBattle.hpp"

#include "System/StateManagerBase.hpp"
#include "Project/ProjectStateManager.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Draw.hpp"
#include "Project/ScrollBackground.hpp"

static int const meter_max = 100;


StateBattle::StateBattle( StateManagerBase& manager )
 : m_manager( manager )
 , m_add_meter(0)
 , m_step( Step_DecideMeter1 )
 , m_player_x(0)
 , m_background( new ScrollBackground() )
 , m_player_speed(0.0f)
 , m_frame(0)
{
    m_meter[0]=0;
    m_meter[1]=0;
}


void StateBattle::Update()
{
    //直ぐリセットできるように
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) )
    {
        m_manager.ChangeState( ProjectState_Battle );
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
	case Step_Result:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
	    {
	    	m_manager.ChangeState( ProjectState_Title );
	    }
		break;
	}
}

void StateBattle::Draw()
{
    m_background->Draw();
	DrawTexture( 50 , 230, ImageType_Player );
	int const x = 100;
	
	for( int i = 0; i < 2 ; i++ ){
    	int const y = 80 * i + 100;
    	DrawCircle( x, y, meter_max / 2, GetColor( 0,0,0 ), TRUE ); 
    	DrawCircle( x, y, m_meter[i] / 2 , GetColor( 0,255 / meter_max * m_meter[i],0 ), TRUE ); 
    }

    DrawFormatString( 0 , 0 , ColorOf() , "m_player_x[%f]", m_player_x );
    DrawFormatString( 0 , 10 , ColorOf() , "m_player_speed[%f]", m_player_speed );
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
	m_player_x += m_player_speed;
    m_background->SetScroll( static_cast<int>(m_player_x) );
	if( m_player_speed < 0.01f ){
		SetStep( Step_Result );
	}
}

