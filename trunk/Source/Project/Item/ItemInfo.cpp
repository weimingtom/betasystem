#include "ItemInfo.hpp"

namespace {

ItemInfo item_info_list[] =
{
    {"ロングヘアー",    0,0,Equip_Head},
    {"ショートヘアー",  0,0,Equip_Head},
    {"ツインテール",    0,0,Equip_Head},
    {"ポニーテール",    0,0,Equip_Head},
    {"セーラー服",      0,0,Equip_Body},
    {"メイド服",        0,0,Equip_Body},
};

} // namespace unnamed


ItemInfo ItemInfoOf( ItemType item_type )
{
    return item_info_list[item_type];
}

