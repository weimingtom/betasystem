#ifndef save_data_hpp
#define save_data_hpp

#include "Item.hpp"

/**
    セーブデータの型.
*/
struct SaveData
{
public:
    SaveData();
    void Save();
    void Load();

public:
    static int const ItemBagSize = 8;
    int m_item[ItemBagSize];
    int m_total_break;
    int m_max_break;
    int m_current_stage;
    int m_player_hp;
    int m_player_mp;
};

/**
    セーブデータ.
    @note シンプルにグローバル変数で持つ.
*/
extern SaveData gSaveData;

#endif // save_data_hpp

