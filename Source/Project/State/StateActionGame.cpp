#include "StateActionGame.hpp"

#include <assert.h>
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "System/CheckHit.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"

static UnitPlayer gUnitPlayer;
static bool gIsVisibleCollision = false;

StateActionGame::StateActionGame()
{
	for( int i = 0 ; i < kEnemyMax ; i++ ){
		mEnemy[i].SetPos( Vector2( GetRand(640), GetRand(-480) ) );
	}
}

void StateActionGame::Update()
{
	//背景描画.
	for( int x = 0; x < 20; x++ ){
		for( int y = 0 ; y < 20 ; y++ ){
			DrawGraph(
				x * 64, y*64,
				ProjectImageLoader::ImageHandleOf( ProjectImageLoader::ImageType_Map ), FALSE );
		}	
	}

    // グリッド.
    {
    	/*
	    int const kLineNum = 20;
	    int const kMargin = 40;
		for( int y = 0; y < kLineNum ; y++ ){
		    DrawLine( 0, y*kMargin, 1000, y*kMargin, ColorOf(50,250,50) );
	    }
	    for( int x = 0; x < kLineNum ; x++ ){
		    DrawLine( x*kMargin, 0, x*kMargin, 1000, ColorOf(50,250,50) );
		}
		*/
	}

	int const kFontSize = 14;
    SetFontSize(kFontSize);
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "アクションゲームテスト:");
    DrawFormatString( 0 , kFontSize , ColorOf(0,255,0) , " player hp %d", gUnitPlayer.GetHP() );
    
    // 衝突判定.
    for( int i = 0; i < kEnemyMax ; i ++ )
    {
    	if( mEnemy[i].IsDead() ){ continue; }
    	if( mEnemy[i].IsDamaged() ){ continue; }
    	if( gUnitPlayer.IsDead() ){ continue; } 
    	if( gUnitPlayer.IsJump() ){ continue; } 
    	if( gUnitPlayer.IsDamaged() ){ continue; } 
    
    	Vector2 const kLeftTop = Vector2( mEnemy[i].GetPos().x - mEnemy[i].GetSize().x / 2 , mEnemy[i].GetPos().y - mEnemy[i].GetSize().y / 2 );
    	
    	if ( CheckHitRect( gUnitPlayer.GetPos(), kLeftTop, mEnemy[i].GetSize() ) ){
	    	
			SingletonSoundLoader::Get()->Play( NameOf(SoundType_OK) );
	    	if( gUnitPlayer.IsDash() ){
	    		Vector2 speed = mEnemy[i].GetPos() - gUnitPlayer.GetPos();
	    		mEnemy[i].SetSpeed( speed.Normalize() * 30 );
	    		mEnemy[i].Damage(10);
	    	}else{
	    		Vector2 speed = gUnitPlayer.GetPos() - mEnemy[i].GetPos();
	    		gUnitPlayer.SetSpeed( speed.Normalize() * 30 );
	    	    gUnitPlayer.Damage(10);
			}
	    }
    }

    SetFontSize(24);

	if( !gUnitPlayer.IsDead() ){

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
	    gUnitPlayer.AddPos( move * 5 );
	    
	    //ダッシュ
	    if(
	    	KeyInput()->IsTrig( InputKey::Type_J )
	    	|| SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left )
	    ){
	    	gUnitPlayer.BeginDash( gUnitPlayer.GetDir() );
	    }

		// ジャンプ
	    if(
			KeyInput()->IsTrig( InputKey::Type_K )
	    	|| SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right )
		){
	    	gUnitPlayer.BeginJump();
	    }

	    if(
			KeyInput()->IsTrig( InputKey::Type_L )
		){
			gIsVisibleCollision = !gIsVisibleCollision;
	    }
		
	    gUnitPlayer.Update();
	    for( int i = 0 ; i < kEnemyMax ; i++ ){
	    	mEnemy[i].Update();
	    }
	}
    gUnitPlayer.Draw();
    for( int i = 0 ; i < kEnemyMax ; i++ ){
    	mEnemy[i].Draw();
    }

    
}

void StateActionGame::Draw()
{
}

