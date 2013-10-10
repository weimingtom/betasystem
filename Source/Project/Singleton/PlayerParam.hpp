#ifndef PLAYER_PARAM_HPP__
#define PLAYER_PARAM_HPP__

#include "Project/Item/ItemInfo.hpp"

//! プレイヤー情報.
struct PlayerParam
{
    static int const ItemMax = 10;
    ItemInfo mItemList[ItemMax];
    ItemInfo mEquipList[EquipPos_Num];
    //! コンストラクタ.
    PlayerParam(){
        for( int i = 0 ; i < ItemMax ; i ++ ){
            mItemList[i].Reset();
        }
        for( int i = 0 ; i < EquipPos_Num ; i++ ){
            mEquipList[i].Reset();
        }
    }
};

extern PlayerParam gPlayerParam;

#endif // save_data_hpp

