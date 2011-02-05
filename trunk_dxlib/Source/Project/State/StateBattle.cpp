#include "StateBattle.hpp"

#include "System/StateManagerBase.hpp"
#include "Project/ProjectStateManager.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Draw.hpp"

StateBattle::StateBattle( StateManagerBase& manager )
 : m_manager( manager )
 , m_meter(0)
 , m_add_meter(0)
{
}

void StateBattle::Update()
{
	UpdateMeter();
	DecideMeter();
}

void StateBattle::Draw()
{
	DrawTexture( 0, 0, ImageType_Forest );
	int const x = 50;
	int const y = 50;
	int const height = 50;
	DrawBox( x, y, x+m_meter, y+height, GetColor( 255,255,255 ), TRUE ); 
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
    }
}

