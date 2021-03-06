﻿#ifndef IncludeGuard_UnitBase_
#define IncludeGuard_UnitBase_

#include "System/Vector2.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

//! ユニットの基底クラス.
class UnitBase
{
public:
	UnitBase();
	virtual ~UnitBase(){}
public:
	virtual void Update();
	virtual void PreDraw();
	//! 描画.
	virtual void Draw();
	virtual bool IsDead() const;
public:
	void DrawUnit( bool is_walk = false, bool is_attack = false );

	//! ジャンプ高さ
	float GetHeight() const;

	//! 座標設定.
	void SetPos( Vector2 pos );

	//! 座標取得.
	Vector2 GetPos() const;

	//! サイズ取得
	Vector2 GetSize() const;

	//! スピード設定.
	void SetSpeed( Vector2 speed );
	void Damage( int damage );
	bool IsDamaged() const;
	int GetHP() const;
	int GetMaxHP() const{ return mHPMax; }
	void AddPos( Vector2 add_pos );
	void AddHP(int add){
		mHP += add;
		if( mHP > mHPMax ){ mHP = mHPMax; }
	}
	
	int GetExp() const{ return mExp; }
	void AddExp( int add_exp ){
		mExp += add_exp;
		if( mExp >= kExpMax ){
			mExp -= kExpMax;
			mLevel++;
			mHPMax += 5;
			mHP = mHPMax;
		}
	}

protected:
	static int const kExpMax = 100;
protected:
	Vector2 mPos;
	Vector2 mSize;
	float mHeight;
	Vector2 mSpeed;
	int mWeight;
	int mHP;
	int mHPMax;
	bool mIsDead;
	int mDamage;
	int mDamageFrame;
	Game::ImageType mImageType;
	Vector2 mImageSize;
	Vector2 mDir;		//!< 向き.
	int mFrame;
	int mAnimIndex;
	bool mIsWalk;
	bool mIsAttack;
	int mExp;
	int mLevel;
	int mAttackFrame;
};

#endif // IncludeGuard_UnitBase_

