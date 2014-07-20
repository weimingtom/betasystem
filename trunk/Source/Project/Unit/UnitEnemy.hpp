#ifndef IncludeGuard_UnitEnemy_
#define IncludeGuard_UnitEnemy_

#include "UnitBase.hpp"
#include "UnitPlayer.hpp"

//! 敵ユニット.
class UnitEnemy : public UnitBase
{
public:
	UnitEnemy(){}
	~UnitEnemy(){}
public:
	virtual void Update() override;
};

#endif // IncludeGuard_UnitEnemy_

