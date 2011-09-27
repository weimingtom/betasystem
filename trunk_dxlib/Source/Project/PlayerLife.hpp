#ifndef include_282651a3_3fe0_46c6_9f1c_f57a69fdf4ab
#define include_282651a3_3fe0_46c6_9f1c_f57a69fdf4ab

/**
	プレイヤーの残機を管理するクラス.
*/
class PlayerLife
{
public:
	PlayerLife(int life_num);
	virtual ~PlayerLife();
public:
	void Add(){ mLifeNum++; }
	void Sub(){ if( mLifeNum > 0 ){ mLifeNum--; } }
	void Draw() const;
	bool IsDead() const{ return (mLifeNum == 0); }
private:
	int mLifeNum;
};

#endif //include_282651a3_3fe0_46c6_9f1c_f57a69fdf4ab

