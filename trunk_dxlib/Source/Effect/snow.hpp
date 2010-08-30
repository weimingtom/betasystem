#pragma once
#include "const.h"

#include <stdlib.h>
#include <math.h>

/*
 * ��N���X
 */
class Snow
{
public:
	Point2D p;    // ���W
	double b;     // �u�����h�l
	bool is;      // �\���t���O
private:
	Point2D mv;   // �ړ���
	Point2D a;    // �����x
	int cnt;      // �\���J�E���g

public:
	Snow();

	void Init();      // ������
	bool Update();    // �X�V
private:
	void SetPoint(double x, double y);   // ���W�ݒ�
	void SetMove(double mx, double my);  // �ړ��ʐݒ�
	void SetAccel(double ax, double ay); // �����x�ݒ�
	bool Move();  // �ړ�
	void Accel(); // ����
};
