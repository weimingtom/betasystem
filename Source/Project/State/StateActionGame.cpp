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
#include "Project/Shot/ShotBase.hpp"
#include "Project/Particle/Particle.hpp"

StateActionGame::StateActionGame()
: mStageFrame(0)
, mPreHoldFrame(0)
, mWalkFrame(0)
, mFrame(0)
{
	InitEnemy();
	gUnitPlayer().Revive();
	
	for( int x = 0; x < kMapChipMax; x++ ){
		for( int y = 0 ; y < kMapChipMax ; y++ ){
			mMapChip[y][x] = 1;
		}
	}
	
	gParticle().Initialize( Vector2(200,200) );
}

void StateActionGame::InitEnemy()
{
	for( int i = 0 ; i < kEnemyMax ; i++ ){
		gUnitEnemy(i).Initialize( EnemyID_Normal );
		gUnitEnemy(i).SetPos( Vector2( GetRand(48*kMapChipMax), GetRand(48*kMapChipMax) ) );
	}
}

void StateActionGame::Update()
{
	mFrame++;
	if( mFrame % 200 == 0 ){
		gUnitPlayer().AddHP(1);
	}

	gCamera2D().SetLookAt( Vector2(0, -mStageFrame ) );
	
	gCamera2D().Update();
	gShotManager().Update();
	gParticle().Update();

	//背景描画.
	for( int x = 0; x < kMapChipMax; x++ ){
		for( int y = 0 ; y < kMapChipMax ; y++ ){
			DrawGraphInCamera(
				Vector2(x*48, y*48),
				Vector2(48,48),
				0,
				mMapChip[y][x] == 0 ?  PrincessImageLoader::ImageType_Map : PrincessImageLoader::ImageType_Map2, FALSE );
		}	
	}

 	int const kFontSize = 14;
 	int y = 0;
    SetFontSize(kFontSize);
    DrawFormatString( 0 , y , ColorOf(0,255,0) , "アクションゲームテスト:");
    DrawFormatString( 0 , y += kFontSize , ColorOf(255,255,0) , " player hp[%d/%d]", gUnitPlayer().GetHP(),gUnitPlayer().GetMaxHP() );
    DrawFormatString( 0 , y += kFontSize , ColorOf(0,255,0) , " 敵復活 - R" );
    DrawFormatString( 0 , y += kFontSize , ColorOf(0,255,0) , " 敵+自分復活 - T" );
    
    // プレイヤーの攻撃.
    for( int i = 0; i < kEnemyMax ; i ++ )
    {
    	if( gUnitEnemy(i).IsDead() ){ continue; }
    	if( gUnitPlayer().IsJump() ){ continue; } 
    	
    	Vector2 const kLeftTop = Vector2( gUnitEnemy(i).GetPos().x - gUnitEnemy(i).GetSize().x / 2 , gUnitEnemy(i).GetPos().y - gUnitEnemy(i).GetSize().y / 2 );
    	
    	if ( CheckHitRect( gUnitPlayer().GetPos(), kLeftTop, gUnitEnemy(i).GetSize() ) ){
	    	if( gUnitPlayer().IsAttack() )
	    	{
	    		Vector2 speed = gUnitPlayer().GetDir() ;
	    		speed.Normalize();
	    		speed *= 5;
	    		gUnitEnemy(i).Damage( gUnitPlayer().GetAttackCanselCount() );
	    		gUnitEnemy(i).SetSpeed( speed );
	    		gUnitPlayer().SetSpeed( speed * -0.1 );
				gUnitPlayer().EndAttack();
				
				SingletonSoundLoader::Get()->Play( NameOf(SoundType_Hit) );
	    	}
	    }
    }

	// お互いに重ならないように
    for( int i = 0; i < kEnemyMax ; i ++ )
    {
    	if( gUnitEnemy(i).IsDead() ){ continue; }
    	Vector2 const kLeftTop = Vector2( gUnitEnemy(i).GetPos().x - gUnitEnemy(i).GetSize().x / 2 , gUnitEnemy(i).GetPos().y - gUnitEnemy(i).GetSize().y / 2 );
    	
    	if ( CheckHitRect( gUnitPlayer().GetPos(), kLeftTop, gUnitEnemy(i).GetSize() ) ){
    		Vector2 speed = gUnitEnemy(i).GetPos() - gUnitPlayer().GetPos() ;
    		speed.Normalize();
    		speed *= 8;
//    		gUnitEnemy(i).AddPos( speed );
    		gUnitPlayer().AddPos( speed * -1 );
	    }
    }

    // 弾ダメージ
    for( int i = 0; i < ShotManager::kShotNum ; i ++ )
    {
    	if( gUnitPlayer().IsJump() ){ continue; } 
    	if( gUnitPlayer().IsDamaged() ){ continue; } 
    	if( !gShotManager().GetShot(i).IsLife() ){ continue; }

		ShotBase const& crTargetShot = gShotManager().GetShot(i);

    	Vector2 const kLeftTop = Vector2(
    		crTargetShot.GetPos().x - crTargetShot.GetSize().x / 2 ,
    		crTargetShot.GetPos().y - crTargetShot.GetSize().y / 2 );
    	
    	if ( CheckHitRect( gUnitPlayer().GetPos(), kLeftTop, crTargetShot.GetSize() ) )
    	{
			SingletonSoundLoader::Get()->Play( NameOf(SoundType_Damaged) );
    		Vector2 speed =  gUnitPlayer().GetPos() - crTargetShot.GetPos();
    		speed.Normalize();
    		gUnitPlayer().Damage(1);
	    }
    }

	OperatePlayer();
	

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
}

/**
	プレイヤ－操作.
*/
void StateActionGame::OperatePlayer()
{
	if( gUnitPlayer().IsDead() ){ return;}

	//移動.
	Vector2 move;
    if( KeyInput()->IsHold( InputKey::Type_A ) ){ move.x -= 1; }
    if( KeyInput()->IsHold( InputKey::Type_D ) ){ move.x += 1; }
    if( KeyInput()->IsHold( InputKey::Type_W ) ){ move.y -= 1; }
    if( KeyInput()->IsHold( InputKey::Type_S ) ){ move.y += 1; }
    move.Normalize();
    if( move.Length() != 0.0f ){ gUnitPlayer().SetDir(move); }

	if(
		!gUnitPlayer().IsDash()
		&& !gUnitPlayer().IsAttack()
		&& !gUnitPlayer().IsAttackLock() 
	){
	    gUnitPlayer().Walk( move * 5 );

	    // 歩き音用
	    if( move.Length() == 0.0f ){
	    	mWalkFrame = 0;
	    }else{
	    	mWalkFrame ++;
	    }
	    if( gUnitPlayer().IsJump() ){
	    	mWalkFrame = 0;
	    }
	    if( mWalkFrame != 0 && mWalkFrame % 16 == 0 ){
	    	//SE鳴らす
			SingletonSoundLoader::Get()->Play( NameOf(SoundType_Walk) );
	    }
	}
    
	//攻撃
	if(
    	KeyInput()->IsTrig( InputKey::Type_J )
    ){
    	gUnitPlayer().BeginAttack( gUnitPlayer().GetDir());
    }

	//ダッシュ
    if(
		KeyInput()->IsTrig( InputKey::Type_K )
    	|| SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right )
	){
    	gUnitPlayer().BeginDash( gUnitPlayer().GetDir() );
    }

	// マウスによる移動処理.
	if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
	{
		bool is_target_enemy = false;
		// 敵検索.
	    for( int i = 0; i < kEnemyMax ; i ++ )
	    {
	    	if( gUnitEnemy(i).IsDead() ){ continue; }
	    	Vector2 const kLeftTop = Vector2( gUnitEnemy(i).GetPos().x - gUnitEnemy(i).GetSize().x / 2 , gUnitEnemy(i).GetPos().y - gUnitEnemy(i).GetSize().y / 2 );
	    	
	    	if ( CheckHitRect( SingletonInputMouse::Get()->Position() - gCamera2D().GetDrawOffset(), kLeftTop, gUnitEnemy(i).GetSize() ) ){
				gUnitPlayer().SetTargetEnemy(i);
				is_target_enemy = true;
				break;
		    }
	    }
		
		if( !is_target_enemy ){
			gUnitPlayer().SetTargetPos( SingletonInputMouse::Get()->Position() - gCamera2D().GetDrawOffset() );
		}
	}


    gUnitPlayer().Update();
    for( int i = 0 ; i < kEnemyMax ; i++ ){
    	gUnitEnemy(i).Update();
    }


	//デバッグ
    if(
		KeyInput()->IsTrig( InputKey::Type_H )
	){
		SetVisibleCollision( !IsVisibleCollision() );
    }
}

void StateActionGame::Draw()
{
	for( int x = 0; x < 5; x++ ){
		for( int y = 0 ; y < 5; y++ ){
			DrawGraphInCamera(
				Vector2(x*200, y*200),
				Vector2(48,48),
				0,
				PrincessImageLoader::ImageType_MapObject,
				TRUE );
		}	
	}
	
    SetFontSize(24);

    for( int i = 0 ; i < kEnemyMax ; i++ ){
    	gUnitEnemy(i).PreDraw();
    }
    gUnitPlayer().PreDraw();

    for( int i = 0 ; i < kEnemyMax ; i++ ){
    	gUnitEnemy(i).Draw();
    }

    gUnitPlayer().Draw();
	gShotManager().Draw();
	gParticle().Draw();
}

