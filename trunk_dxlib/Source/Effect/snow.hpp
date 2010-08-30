#ifndef include_7eacc4fc_e44f_4582_9c86_468b1a4712f0
#define include_7eacc4fc_e44f_4582_9c86_468b1a4712f0

#include "System/Vector2.hpp"

/*
 * 雪クラス
 */
class Snow
{
public:
	Vector2 p;    // 座標
	double b;     // ブレンド値
	bool is;      // 表示フラグ
private:
	Vector2 mv;   // 移動量
	Vector2 a;    // 加速度
	int cnt;      // 表示カウント

public:
	Snow();

	void Init();      // 初期化
	bool Update();    // 更新
private:
	void SetPoint(double x, double y);   // 座標設定
	void SetMove(double mx, double my);  // 移動量設定
	void SetAccel(double ax, double ay); // 加速度設定
	bool Move();  // 移動
	void Accel(); // 加速
};

#endif // include_7eacc4fc_e44f_4582_9c86_468b1a4712f0

