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
#include "Project/Unit/UnitPlayer.hpp"
#include "Project/Unit/UnitBase.hpp"
#include "Project/Unit/Global.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

#include "Project/Camera2D/Camera2D.hpp"

StateActionGame::StateActionGame()
: mStageFrame(0)
{
	InitEnemy();
	gUnitPlayer().Revive();
}

void StateActionGame::InitEnemy()
{
	for( int i = 0 ; i < kEnemyMax ; i++ ){
		mEnemy[i].Initialize( EnemyID_Normal );
//		mEnemy[i].Initialize( static_cast<EnemyID>( GetRand(EnemyID_Num-1) ) );
		mEnemy[i].SetPos( Vector2( -320 + GetRand(640), - 240 + GetRand(-480*10) ) );
	}
}

void StateActionGame::Update()
{
	if( mStageFrame < 3000 ){
//		mStageFrame++;
	}
	gCamera2D().SetLookAt( Vector2(0, -mStageFrame ) );
	
	gCamera2D().Update();

	//背景描画.
	for( int x = 0; x < 10; x++ ){
		for( int y = 0 ; y < 100 ; y++ ){
			DrawGraphInCamera(
				-320 + x*64, -y*64,
					PrincessImageLoader::ImageType_Map, FALSE );
		}	
	}

 	int const kFontSize = 14;
 	int y = 0;
    SetFontSize(kFontSize);
    DrawFormatString( 0 , y += kFontSize , ColorOf(0,255,0) , "アクションゲームテスト:");
    DrawFormatString( 0 , y += kFontSize , ColorOf(0,255,0) , " player hp %d", gUnitPlayer().GetHP() );
    DrawFormatString( 0 , y += kFontSize , ColorOf(0,255,0) , " 敵復活 - R" );
    DrawFormatString( 0 , y += kFontSize , ColorOf(0,255,0) , " 敵+自分復活 - T" );
    
    // 衝突判定プレイヤーの攻撃.
    for( int i = 0; i < kEnemyMax ; i ++ )
    {
    	if( mEnemy[i].IsDead() ){ continue; }
    	if( gUnitPlayer().IsJump() ){ continue; } 
    	if( gUnitPlayer().IsDamaged() ){ continue; } 
    	
    	Vector2 const kLeftTop = Vector2( mEnemy[i].GetPos().x - mEnemy[i].GetSize().x / 2 , mEnemy[i].GetPos().y - mEnemy[i].GetSize().y / 2 );
    	
    	if ( CheckHitRect( gUnitPlayer().GetPos(), kLeftTop, mEnemy[i].GetSize() ) ){
	    	if(
	    		gUnitPlayer().IsDash()
	    		&& ( gUnitPlayer().GetAttackID() != mEnemy[i].GetDamagedID() )
	    	)
	    	{
				SingletonSoundLoader::Get()->Play( NameOf(SoundType_OK) );
	    		Vector2 speed = mEnemy[i].GetPos() - gUnitPlayer().GetPos();
	    		mEnemy[i].SetSpeed( speed.Normalize() );
	    		mEnemy[i].Damage(1);
	    		mEnemy[i].SetDamagedID( gUnitPlayer().GetAttackID() );
	    		gUnitPlayer().FreeLock();
	    	}
	    }
    }

    // 敵からの攻撃.
    for( int i = 0; i < kEnemyMax ; i ++ )
    {
    	if( mEnemy[i].IsDead() ){ continue; }
    	if( mEnemy[i].IsDamaged() ){ continue; } 
    	if( gUnitPlayer().IsJump() ){ continue; } 
    	if( gUnitPlayer().IsDamaged() ){ continue; } 
    	if( gUnitPlayer().IsDash() ){ continue; } 
    	
    	Vector2 const kLeftTop = Vector2( mEnemy[i].GetPos().x - mEnemy[i].GetSize().x / 2 , mEnemy[i].GetPos().y - mEnemy[i].GetSize().y / 2 );
    	
    	if ( CheckHitRect( gUnitPlayer().GetPos(), kLeftTop, mEnemy[i].GetSize() ) ){
			SingletonSoundLoader::Get()->Play( NameOf(SoundType_OK) );
    		Vector2 speed = gUnitPlayer().GetPos() - mEnemy[i].GetPos();
    		gUnitPlayer().SetSpeed( speed.Normalize() );
    	    gUnitPlayer().Damage(1);
		}
	}

    SetFontSize(24);

	if( !gUnitPlayer().IsDead() ){

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
	    gUnitPlayer().AddPos( move * 5 );
	    
	    //ダッシュ
	    if(
	    	KeyInput()->IsTrig( InputKey::Type_J )
	    	|| SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left )
	    ){
	    	gUnitPlayer().BeginDash( gUnitPlayer().GetDir() );
	    }

		// ジャンプ
	    if(
			KeyInput()->IsTrig( InputKey::Type_K )
	    	|| SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right )
		){
	    	gUnitPlayer().BeginJump();
	    }

	    if(
			KeyInput()->IsTrig( InputKey::Type_L )
		){
			SetVisibleCollision( !IsVisibleCollision() );
	    }

		
	    gUnitPlayer().Update();
	    for( int i = 0 ; i < kEnemyMax ; i++ ){
	    	mEnemy[i].Update();
	    }
	}

	// デバッグ処理.
    if(
		KeyInput()->IsTrig( InputKey::Type_R )
	){
		InitEnemy();
    }

    if(
		KeyInput()->IsTrig( InputKey::Type_T )
	){
		InitEnemy();
		gUnitPlayer().Revive();
    }


    for( int i = 0 ; i < kEnemyMax ; i++ ){
    	mEnemy[i].PreDraw();
    }
    gUnitPlayer().PreDraw();

    for( int i = 0 ; i < kEnemyMax ; i++ ){
    	mEnemy[i].Draw();
    }
    gUnitPlayer().Draw();
}

void StateActionGame::Draw()
{
}

