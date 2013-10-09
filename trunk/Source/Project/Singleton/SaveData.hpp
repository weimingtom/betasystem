#ifndef save_data_hpp
#define save_data_hpp

#include "Project/Item/ItemInfo.hpp"

struct Player
{
    ItemInfo item_list[100];
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

