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
	void BeginAttack( Vector2 dash_vec );
	//! ジャンプする
	void BeginJump();
	bool IsDash() const;
	bool IsSpecialDash() const;
	bool IsJump() const;
	void Walk( Vector2 add_pos );
	Vector2 GetDir() const;
	//! 生き返る.
	void Revive();
	//! 硬直を消す.
	void FreeLock();
	//! ダッシュ回数.
	int GetAttackID() const { return mDashIDCount; }
private:
	static int const kDefaultHP = 10;
private:
	int mDashFrame;
	int mSpecialDashFrame;
	float mGravity;		//!< 重力
	int mDashLockFrame;
	int mDashIDCount;
	bool mIsWalk;
};

UnitPlayer& gUnitPlayer();

#endif // IncludeGuard_UnitPlayer_
