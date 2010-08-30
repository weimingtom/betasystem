#ifndef include_7eacc4fc_e44f_4582_9c86_468b1a4712f0
#define include_7eacc4fc_e44f_4582_9c86_468b1a4712f0

#include "System/Vector2.hpp"

/*
 * ��N���X
 */
class Snow
{
public:
	Vector2 p;    // ���W
	double b;     // �u�����h�l
	bool is;      // �\���t���O
private:
	Vector2 mv;   // �ړ���
	Vector2 a;    // �����x
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

#endif // include_7eacc4fc_e44f_4582_9c86_468b1a4712f0

