#ifndef AVATER_HPP__
#define AVATER_HPP__

#include "Project/Item/ItemInfo.hpp"

//! �A�o�^�[�N���X.
//! �����ꗗ��n���ƁADraw�ł��̑��������ăL������\�������邱�Ƃ��o����.
class Avater
{
public:
	Avater( ItemInfo equip_list[EquipPos_Num] );
	~Avater();
public:
	void Draw(int x,int y) const;
private:
    ItemInfo mEquipList[EquipPos_Num];
    int mHairImageHandle; //!< �J���[�p���b�g�����������Ƃ̔��̖уe�N�X�`���̃n���h��.
};


#endif // AVATER_HPP__
