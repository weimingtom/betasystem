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
			mMapChip[y][x] = GetRand(1);
		}
	}
}

void StateActionGame::InitEnemy()
{
	for( int i = 0 ; i < kEnemyMax ; i++ ){
		mEnemy[i].Initialize( EnemyID_Normal );
//		mEnemy[i].Initialize( static_cast<EnemyID>( GetRand(1) ) );
		mEnemy[i].SetPos( Vector2( GetRand(48*kMapChipMax), GetRand(48*kMapChipMax) ) );
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

	//背景描画.
	for( int x = 0; x < kMapChipMax; x++ ){
		for( int y = 0 ; y < kMapChipMax ; y++ ){
			DrawGraphInCamera(
				x*48, y*48,
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
    	if( mEnemy[i].IsDead() ){ continue; }
    	if( gUnitPlayer().IsJump() ){ continue; } 
    	
    	Vector2 const kLeftTop = Vector2( mEnemy[i].GetPos().x - mEnemy[i].GetSize().x / 2 , mEnemy[i].GetPos().y - mEnemy[i].GetSize().y / 2 );
    	
    	if ( CheckHitRect( gUnitPlayer().GetPos(), kLeftTop, mEnemy[i].GetSize() ) ){
	    	if(
	    		gUnitPlayer().IsDash()
	    		&& ( gUnitPlayer().GetAttackID() != mEnemy[i].GetDamagedID() )
	    	)
	    	{
				SingletonSoundLoader::Get()->Play( NameOf(SoundType_Hit) );

	    		mEnemy[i].SetDamagedID( gUnitPlayer().GetAttackID() );

	    		Vector2 speed = gUnitPlayer().GetDir() ;
	    		speed.Normalize();
	    		speed *= 5;
	    		mEnemy[i].Damage(1);
	    		mEnemy[i].SetSpeed( speed );
	    		gUnitPlayer().SetSpeed( speed * -0.1 );
	    		gUnitPlayer().FreeLock();
	    	}
	    }
    }

	// お互いに重ならないように
    for( int i = 0; i < kEnemyMax ; i ++ )
    {
    	if( mEnemy[i].IsDead() ){ continue; }
    	Vector2 const kLeftTop = Vector2( mEnemy[i].GetPos().x - mEnemy[i].GetSize().x / 2 , mEnemy[i].GetPos().y - mEnemy[i].GetSize().y / 2 );
    	
    	if ( CheckHitRect( gUnitPlayer().GetPos(), kLeftTop, mEnemy[i].GetSize() ) ){
    		Vector2 speed = mEnemy[i].GetPos() - gUnitPlayer().GetPos() ;
    		speed.Normalize();
    		speed *= 4;
    		mEnemy[i].AddPos( speed );
    		gUnitPlayer().AddPos( speed * -1 );
	    }
    }

    // 弾ダメージ
    for( int i = 0; i < ShotManager::kShotNum ; i ++ )
    {
    	if( gUnitPlayer().IsJump() ){ continue; } 
    	if( gUnitPlayer().IsDamaged() ){ continue; } 
    	if( gUnitPlayer().IsSpecialDash() ){ continue; } 
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
    		gUnitPlayer().SetSpeed( speed * 10 );
    		gUnitPlayer().Damage(1);
	    }
    }


    SetFontSize(24);

	if( !gUnitPlayer().IsDead() ){

		//移動.
		Vector2 move;
		if( !gUnitPlayer().IsDash() ){
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
		}
	    move.Normalize();
	    gUnitPlayer().Walk( move * 5 );
	    
		//攻撃
		if(
	    	KeyInput()->IsTrig( InputKey::Type_J )
	    	|| SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left )
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

	    if(
			KeyInput()->IsTrig( InputKey::Type_H )
		){
			SetVisibleCollision( !IsVisibleCollision() );
	    }

	    gUnitPlayer().Update();
	    for( int i = 0 ; i < kEnemyMax ; i++ ){
	    	mEnemy[i].Update();
	    }

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

	gShotManager().Draw();
}

void StateActionGame::Draw()
{
}

