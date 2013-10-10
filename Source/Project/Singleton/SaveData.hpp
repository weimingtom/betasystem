#ifndef save_data_hpp
#define save_data_hpp

#include "Project/Item/ItemInfo.hpp"

struct Player
{
    static int const ItemMax = 100;
    ItemInfo mItemList[ItemMax];
    Player()
    {
        for( int i = 0 ; i < ItemMax ; i ++ ){
            mItemList[i].Reset();
        }
    }
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

