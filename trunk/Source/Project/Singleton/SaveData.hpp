#ifndef save_data_hpp
#define save_data_hpp

#include "Project/Item/ItemInfo.hpp"

struct Player
{
    static int const ItemMax = 100;
    ItemInfo item_list[ItemMax];
};

/**
    セーブデータの型.
*/
struct SaveData
{
public:
    SaveData();
    ~SaveData();
    void Save();
    void Load();

public:
    Player mPlayer;
};

/**
    セーブデータ.
    @note シンプルにグローバル変数で持つ.
*/
extern SaveData gSaveData;

#endif // save_data_hpp

