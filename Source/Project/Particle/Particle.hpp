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
	}
	void Draw()
	{
		if( !IsLife() ){ return; }

		SetDrawBlendMode( DX_BLENDMODE_ADD, 255 ) ;
	    DrawGraphInCamera( 
	    	static_cast<int>( mPos.x - mSize.x / 2 ),
	    	static_cast<int>( mPos.y - mSize.y / 2 ) ,
			PrincessImageLoader::ImageType_Shot,
			TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 ) ;
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
			if( GetRand(30) == 0 ){ 
				Vector2 dir;
				float x = static_cast<float>( GetRand(200) - 100 );
				float y = static_cast<float>( GetRand(200) - 100 );
				dir.x = x / 100 ;
				dir.y = y / 100 ;
				mParticlePartsList[i].Initialize(mPos,dir,60);
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
	static int const kPartsNum = 32;
	ParticleParts mParticlePartsList[kPartsNum];
	Vector2 mPos;
};

//! パーティクルインスタンスの取得.
Particle& gParticle();


#endif 

