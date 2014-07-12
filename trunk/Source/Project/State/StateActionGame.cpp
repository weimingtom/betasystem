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
		static_cast<int>(mPlayerStatus.GetPos().x),
		static_cast<int>(mPlayerStatus.GetPos().y +4.0f),
		ColorOf(155,155,155), "●" );
    // プレイヤー
	DrawFormatString(
		static_cast<int>(mPlayerStatus.GetPos().x),
		static_cast<int>(mPlayerStatus.GetPos().y),
		ColorOf(255,255,255), "●" );
	if( mPlayerStatus.IsAttack() ){
	    // 攻撃判定
		DrawFormatString(
			static_cast<int>( mPlayerStatus.GetPos().x + mPlayerStatus.GetDir().x * 3 ),
			static_cast<int>( mPlayerStatus.GetPos().y + mPlayerStatus.GetDir().y * 3 ),
			ColorOf(255,55,55), "●" );
		DrawFormatString(
			static_cast<int>( mPlayerStatus.GetPos().x + mPlayerStatus.GetDir().x * 6 ),
			static_cast<int>( mPlayerStatus.GetPos().y + mPlayerStatus.GetDir().y * 6 ),
			ColorOf(255,55,55), "●" );
	}
   
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
    	mPlayerStatus.BeginDash( move );
    }

    if( KeyInput()->IsTrig( InputKey::Type_K ) ){
    	// アタック
    	mPlayerStatus.BeginAttack();
    }

    move.Normalize();
    mPlayerStatus.AddPos( move * 3 );
    
    DrawFormatString( 0 , 20 , ColorOf(0,255,0) , "length %f, dir_x %f, dir_y %f", move.Length(), mPlayerStatus.GetDir().x, mPlayerStatus.GetDir().y );
    mPlayerStatus.Update();
}

void StateActionGame::Draw()
{
}

