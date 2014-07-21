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
	UnitEnemy() : mEnemyID(EnemyID_Normal) {}
	~UnitEnemy(){}
public:
	void Initialize( EnemyID enemy_id );
	virtual void Update() override;
	virtual void Draw() override;
private:
	EnemyID mEnemyID;
	int mMoveSpeed;
};

#endif // IncludeGuard_UnitEnemy_

