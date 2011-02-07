#include "StateBattle.hpp"

#include "System/StateManagerBase.hpp"
#include "Project/ProjectStateManager.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Draw.hpp"
#include "Project/ScrollBackground.hpp"

StateBattle::StateBattle( StateManagerBase& manager )
 : m_manager( manager )
 , m_meter(0)
 , m_add_meter(0)
 , m_step( Step_DecideMeter )
 , m_player_x(0)
 , m_background( new ScrollBackground() )
 , m_player_speed(0.0f)
{
}

void StateBattle::Update()
{
	switch( m_step )
	{
	case Step_DecideMeter:
		UpdateMeter();
		DecideMeter();
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
	DrawTexture( 0 , 200, ImageType_Player );
	int const x = 50;
	int const y = 50;
	int const height = 50;
	DrawBox( x, y, x+m_meter, y+height, GetColor( 255,255,255 ), TRUE ); 

    DrawFormatString( 0 , 0 , ColorOf() , "m_player_x[%d]", m_player_x );
}
/**
	メーターの更新.
*/
void StateBattle::UpdateMeter()
{
	m_meter += m_add_meter;
	if( m_meter >= 100 ){
		m_add_meter = -1;
	}
	if( m_meter <= 0){
		m_add_meter = 1;
	}
}
/**
	メーターの数値の決定.
*/
void StateBattle::DecideMeter()
{
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
    	m_add_meter = 0;
    	m_player_speed = static_cast<float>(m_meter); //!< 初速の決定.
    	SetStep( Step_Dash );
    }
}

void StateBattle::SetStep( Step step )
{
	m_step = step;
}

void StateBattle::DashPlayer()
{
	m_player_speed *= 0.98f; //!< 推進力減退.
	m_player_x += m_player_speed;
    m_background->SetScroll( static_cast<int>(m_player_x) );
	if( m_player_speed < 0.01f ){
		SetStep( Step_Result );
	}
}

