#include "StateActionGame.hpp"

#include <assert.h>
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"

StateActionGame::StateActionGame()
{
}

void StateActionGame::Update()
{
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "アクションゲームテスト:");
    
    // 影
	DrawFormatString(
		static_cast<int>(mPlayer.GetPos().x),
		static_cast<int>(mPlayer.GetPos().y +4.0f),
		ColorOf(155,155,155), "●" );
    // プレイヤー
	DrawFormatString(
		static_cast<int>(mPlayer.GetPos().x),
		static_cast<int>(mPlayer.GetPos().y - mPlayer.GetHeight() ),
		ColorOf(255,255,255), "●" );
	DrawFormatString(
		static_cast<int>( mPlayer.GetPos().x + mPlayer.GetDir().x * 2 ),
		static_cast<int>( mPlayer.GetPos().y - mPlayer.GetHeight() + mPlayer.GetDir().y * 2 ),
		ColorOf(255,255,255), "●" );

	Vector2 move;
   
    if( KeyInput()->IsHold( InputKey::Type_A ) ){
    	move.x -= 1;
    }
    if( KeyInput()->IsHold( InputKey::Type_D ) ){
    	move.x += 1;
    }
    if( KeyInput()->IsHold( InputKey::Type_W ) ){
    	move.y -= 1;
    }
    if( KeyInput()->IsHold( InputKey::Type_S ) ){
    	move.y += 1;
    }
    
    if( KeyInput()->IsTrig( InputKey::Type_J ) ){
    	mPlayer.BeginDash( move );
    }

    if( KeyInput()->IsTrig( InputKey::Type_K ) ){
    	mPlayer.BeginJump();
    }

    move.Normalize();
    mPlayer.AddPos( move * 3 );
    
    DrawFormatString( 0 , 20 , ColorOf(0,255,0) , "length %f, dir_x %f, dir_y %f", move.Length(), mPlayer.GetDir().x, mPlayer.GetDir().y );
    mPlayer.Update();
}

void StateActionGame::Draw()
{
}

