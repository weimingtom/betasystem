﻿#ifndef ITEM_INFO_HPP__
#define ITEM_INFO_HPP__

//! アイテムの種類.
enum ItemType
{
	Item_None,
	Item_Hair0,
	Item_Hair1,
	Item_Hair2,
	Item_Hair3,
	Item_Cloth0,
	Item_Cloth1,
	ItemType_Num,
};

//! 装備箇所
enum EquipPos
{
	EquipPos_Hair,
	EquipPos_Body,
	EquipPos_Num,
	EquipPos_None, //!< 装備する場所が無い.
};

//! アイテム詳細情報
struct ItemInfo
{
    ItemType item_type;
    int id;
	int color;
	int level;
	EquipPos equip_pos;
	//! 初期化.
	void Reset()
	{
	    item_type = Item_None;
	    id = 0;
	    color = 0;
	    level = 0;
	    equip_pos = EquipPos_None;
	}
	//! 装備かどうか.
	bool IsEquip() const{ return ( equip_pos != EquipPos_None ); }
};

//! アイテム情報の取得.
ItemInfo ItemInfoOf(ItemType);

//! アイテム名の取得.
char const* NameOf(ItemType);

#endif // ITEM_INFO_HPP__
