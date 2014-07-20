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
	bool IsDead() const;
	bool IsDamaged() const;
	int GetHP() const;
	
protected:
	Vector2 mPos;
	Vector2 mSize;
	float mHeight;
	Vector2 mSpeed;
	int mHP;
	bool mIsDead;
	int mDamageFrame;
	ProjectImageLoader::ImageType mImageType;
	Vector2 mImageSize;
	Vector2 mDir;		//!< 向き.
};

#endif // IncludeGuard_UnitBase_
