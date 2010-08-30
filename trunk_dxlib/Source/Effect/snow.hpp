#pragma once
#include "const.h"

#include <stdlib.h>
#include <math.h>

/*
 * 雪クラス
 */
class Snow
{
public:
	Point2D p;    // 座標
	double b;     // ブレンド値
	bool is;      // 表示フラグ
private:
	Point2D mv;   // 移動量
	Point2D a;    // 加速度
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
