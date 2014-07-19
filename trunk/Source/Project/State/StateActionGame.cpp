﻿#include "StateActionGame.hpp"

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
	for( int i = 0 ; i < kEnemyMax ; i++ ){
		mEnemy[i].SetPos( Vector2( GetRand(640), GetRand(480) ) );
	}
}

void StateActionGame::Update()
{
    // グリッド.
    int const kLineNum = 20;
    int const kMargin = 40;
	for( int y = 0; y < kLineNum ; y++ ){
	    DrawLine( 0, y*kMargin, 1000, y*kMargin, ColorOf(50,50,50) );
    }
    for( int x = 0; x < kLineNum ; x++ ){
	    DrawLine( x*kMargin, 0, x*kMargin, 1000, ColorOf(50,50,50) );
	}

    SetFontSize(10);
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "アクションゲームテスト:");
    DrawFormatString( 0 , 20 , ColorOf(0,255,0) , " dir_x %f, dir_y %f", mPlayer.GetDir().x, mPlayer.GetDir().y );

    SetFontSize(24);

	//移動.
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
    move.Normalize();
    mPlayer.AddPos( move * 5 );
    
    //ダッシュ
    if(
    	KeyInput()->IsTrig( InputKey::Type_J )
    	|| SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left )
    ){
    	mPlayer.BeginDash( mPlayer.GetDir() );
    }

	// ジャンプ
    if(
		KeyInput()->IsTrig( InputKey::Type_K )
    	|| SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right )
	){
    	mPlayer.BeginJump();
    }
    
    mPlayer.Update();
    mPlayer.Draw();
    
    for( int i = 0 ; i < kEnemyMax ; i++ ){
    	mEnemy[i].Update();
    	mEnemy[i].Draw();
    }
    
}

void StateActionGame::Draw()
{
}

