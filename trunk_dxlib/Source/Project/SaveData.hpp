#ifndef save_data_hpp
#define save_data_hpp

#include "Item.hpp"

/**
    セーブデータの型.
*/
struct SaveData{
    int m_item[ItemType_Num];
    int m_total_break;
    /**
        初期化.
    */
    SaveData(){
        for( int i = 0 ; i < ItemType_Num ; i ++ ){
            m_item[i] = 0;
        }
        m_total_break = 0;
    }
};

/**
    セーブデータ.
    @note シンプルにグローバル変数で持つ.
*/
extern SaveData gSaveData;

#endif // save_data_hpp

