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
	//! ダッシュする
	void BeginDash( Vector2 dash_vec );
	//! ジャンプする
	void BeginJump();
	bool IsDash() const;
	bool IsJump() const;
	void AddPos( Vector2 add_pos );
	Vector2 GetDir() const;
private:
	bool mDashFlag;
	float mGravity;		//!< 重力
};


#endif // IncludeGuard_UnitPlayer_
