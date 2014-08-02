#ifndef IncludeGuard_UnitPlayer_
#define IncludeGuard_UnitPlayer_

#include "UnitBase.hpp"

//! プレイヤーユニット.
class UnitPlayer : public UnitBase
{
public:
	UnitPlayer();
public:
	virtual void Update() override;
	virtual void Draw() override;
public:
	//! ダッシュする
	void BeginDash( Vector2 dash_vec );
	//! 攻撃
	void BeginAttack( Vector2 dash_vec );
	//! 
	void EndAttack(){ mAttackFrame = 0; }
	//! 攻撃中かどうか
	bool IsAttack() const{ return( mAttackFrame != 0 ); }
	//! 歩き
	void Walk( Vector2 add_pos );
	//! 向き取得.
	Vector2 GetDir() const;
	//! 生き返る.
	void Revive();
	//! 硬直を消す.
	void FreeLock();
	//! ジャンプしているかどうか.
	bool IsJump() const;
	//!
	int GetAttackID() const { return mAttackCanselCount; }
	//! 
	bool IsDash() const;
	//! 
	int GetAttackCanselCount() const{ return mAttackCanselCount; }
private:
	//! ジャンプする
	void BeginJump();
	//! 
	bool CanAttack() const;
private:
	static int const kDefaultHP = 10;
private:
	int mDashFrame;
	int mSpecialDashFrame;
	float mGravity;		//!< 重力
	int mDashLockFrame;
	bool mIsWalk;
	int mAttackFrame;
	int mAttackLockFrame;
	int mAttackCanselCount;
};

UnitPlayer& gUnitPlayer();

#endif // IncludeGuard_UnitPlayer_
