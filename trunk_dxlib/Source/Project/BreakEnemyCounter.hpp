#ifndef include_71d44d28_3500_49a5_883b_345884e2a986
#define include_71d44d28_3500_49a5_883b_345884e2a986

class BreakEnemyCounter
{
public:
	BreakEnemyCounter();
	~BreakEnemyCounter();
public:
	void Add() { mBreakNum++; }
	int Num() const{ return mBreakNum; }
	void Draw() const;
private:
	int mBreakNum;
};

#endif // include_71d44d28_3500_49a5_883b_345884e2a986

