#ifndef ITEM_INFO_HPP__
#define ITEM_INFO_HPP__

//! アイテムの種類.
enum ItemType
{
	Item_None,
	Item_Hair0,
	Item_Hair1,
	Item_Cloth0,
	Item_Cloth1,
};

//! 装備箇所
enum EquipPosition
{
	Equip_None, //!< 装備する場所が無い.
	Equip_Head,
	Equip_Hair,
	Equip_Body,
	Equip_Option,
	Equip_Num,
};

//! アイテム詳細情報
struct ItemInfo
{
    ItemType item_type;
	int color;
	int level;
	EquipPosition equip_pos;
};

//! アイテム情報の取得.
ItemInfo ItemInfoOf(ItemType);

//! アイテム名の取得.
char const* NameOf(ItemType);

#endif // ITEM_INFO_HPP__
