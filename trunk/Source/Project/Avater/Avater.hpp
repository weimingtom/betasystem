#ifndef AVATER_HPP__
#define AVATER_HPP__

#include "Project/Item/ItemInfo.hpp"

//! アバタークラス.
//! 装備一覧を渡すと、Drawでその装備をつけてキャラを表示させることが出来る.
class Avater
{
public:
	Avater( ItemInfo equip_list[EquipPos_Num] );
	~Avater();
public:
	void Draw(int x,int y) const;
};


#endif // AVATER_HPP__
