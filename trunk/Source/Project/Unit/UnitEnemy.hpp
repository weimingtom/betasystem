#ifndef IncludeGuard_UnitEnemy_
#define IncludeGuard_UnitEnemy_

#include "UnitBase.hpp"
#include "UnitPlayer.hpp"

//! 敵の種類.
enum EnemyID{
	EnemyID_Normal,
	EnemyID_Speed,
	EnemyID_HighSpeed,
	EnemyID_WeightSlime,
	EnemyID_Num,
};

//! 敵ユニット.
class UnitEnemy : public UnitBase
{
public:
	UnitEnemy();
	~UnitEnemy(){}
public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool IsDead() const override;
public:
	void Initialize( EnemyID enemy_id );
private:
	enum State{
		State_Idle,			//!< 待機状態.
		State_Exclamation,	//!< 気付き状態.
		State_Chase,		//!< 追尾状態.
		State_ShotReady,	//!< 攻撃準備.
		State_Shot,			//!< 攻撃.
		State_DeadRequest,	//!< 死亡準備.
		State_Dead,			//!< 死亡
	};
private:
	EnemyID mEnemyID;
	int mMoveSpeed;
	State mState;
	int mFrame;
	bool mIsFollowShot;
};

#endif // IncludeGuard_UnitEnemy_

