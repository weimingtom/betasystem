#include "Item.hpp"

FieldItemManager& gFieldItemManager()
{
	static FieldItemManager sFieldItemManager;
	return sFieldItemManager;
}

PlayerItemList& gPlayerItemList()
{
	static PlayerItemList sPlayerItemList;
	return sPlayerItemList;
}

