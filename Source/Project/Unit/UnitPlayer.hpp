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
	//! ジャンプする
	void BeginJump();
	bool IsDash() const;
	bool IsJump() const;
	void AddPos( Vector2 add_pos );
	Vector2 GetDir() const;
	//! 生き返る.
	void Revive();
	//! 硬直を消す.
	void FreeLock();
private:
	int mDashFrame;
	float mGravity;		//!< 重力
	int mDashLockFrame;
};

UnitPlayer& gUnitPlayer();

#endif // IncludeGuard_UnitPlayer_
