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
    int m_item[ItemType_Num];
    int m_total_break;
    int m_max_break;
};

/**
    セーブデータ.
    @note シンプルにグローバル変数で持つ.
*/
extern SaveData gSaveData;

#endif // save_data_hpp

