#include "Item.hpp"

FieldItemManager& gFieldItemManager()
{
	static FieldItemManager sFieldItemManager;
	return sFieldItemManager;
}

