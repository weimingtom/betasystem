#ifndef Princess_Particle_hpp_
#define Princess_Particle_hpp_

#include "System/Vector2.hpp"
#include "Project/Unit/Global.hpp"

//! パーティクルの１粒.
class ParticleParts
{
public:
	ParticleParts()
	: mLifeFrame(0)
	{
	}
public:
	void Initialize( Vector2 pos, Vector2 dir, int life_frame )
	{
		mPos = pos;
		mDir = dir;
		mLifeFrame = life_frame;
	}
public:
	void Update()
	{
		if( !IsLife() ){ return; }
		if( mLifeFrame ){ mLifeFrame --; }
		mPos += mDir;

		mDir.y -= 0.02f;
		mDir.x *= 0.98f;
	}
	void Draw()
	{
		if( !IsLife() ){ return; }

		SetDrawBlendMode( DX_BLENDMODE_ADD , mLifeFrame*3 ) ;
	    DrawGraphInCamera( 
	    	Vector2( ( mPos.x - mSize.x / 2 ), ( mPos.y - mSize.y / 2 ) ),
			Vector2( 16,16 ),
			0,
			Princess::ImageType_Particle,
			TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0) ;
	}
	bool IsLife() const
	{
		return (mLifeFrame != 0);
	}
private:
	Vector2 mPos;
	Vector2 mSize;
	Vector2 mDir;
	int mLifeFrame;
};

//! パーティクル.
class Particle
{
public:
	//! 初期化.
	void Initialize( Vector2 pos )
	{
		mPos = pos ;
	}
	void Update()
	{
		for( int i = 0 ; i < kPartsNum ; i++ ){

			if( mParticlePartsList[i].IsLife() ){ continue; }
			if( GetRand(20) == 0 ){ 
				Vector2 dir;
				float x = static_cast<float>( GetRand(200) - 100 );
				float y = static_cast<float>( GetRand(200) - 100 );
				dir.x = x / 100 ;
				dir.y = y / 100 ;
				mParticlePartsList[i].Initialize( mPos , dir/2 ,60 + GetRand(30));
			}
		}

		for( int i = 0 ; i < kPartsNum ; i++ ){
			mParticlePartsList[i].Update();
		}
	}
	void Draw()
	{
		for( int i = 0 ; i < kPartsNum ; i++ ){
			mParticlePartsList[i].Draw();
		}
	}
private:
	static int const kPartsNum = 128;
	ParticleParts mParticlePartsList[kPartsNum];
	Vector2 mPos;
};

//! パーティクルインスタンスの取得.
Particle& gParticle();


#endif 

