#include "ItemInfo.hpp"

namespace {

//! アイテム情報.
ItemInfo item_info_list[] =
{
    {Item_None,     0,0,EquipPos_None},
    {Item_Hair0,    0,0,EquipPos_Hair},
    {Item_Hair1,    0,0,EquipPos_Hair},
    {Item_Cloth0,   0,0,EquipPos_Body},
    {Item_Cloth1,   0,0,EquipPos_Body},
};

//! アイテム名.
char const* item_name_list[] =
{
    "なし",
    "髪の毛１",
    "髪の毛２",
    "服１",
    "服２",
};

} // namespace unnamed


ItemInfo ItemInfoOf( ItemType item_type )
{
    return item_info_list[ item_type ];
}

char const* NameOf( ItemType item_type )
{
    return item_name_list[ item_type ];
}

