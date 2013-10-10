#include "StateEquipTest.hpp"

#include "Project/Singleton/SaveData.hpp"
#include "System/ArraySize.hpp"

StateEquipTest::StateEquipTest()
{
    //プレイヤーにいくつかアイテム持たせる。
    gSaveData.mPlayer.mItemList[0] = ItemInfoOf(Item_Hair0);
    gSaveData.mPlayer.mItemList[1] = ItemInfoOf(Item_Hair1);
    gSaveData.mPlayer.mItemList[2] = ItemInfoOf(Item_Cloth0);
    gSaveData.mPlayer.mItemList[3] = ItemInfoOf(Item_Cloth1);
}

StateEquipTest::~StateEquipTest()
{
}

void StateEquipTest::Update()
{
    //上下でアイテム選択.
    //決定で装備アイテムなら装備.
}

void StateEquipTest::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "装備テスト");
    
    //所持アイテムの表示.
    for(int i = 0 ; i < Player::ItemMax ; i++ ){
        DrawFormatString( 50 , 50 + i*15 , GetColor(0,255,0) , NameOf( gSaveData.mPlayer.mItemList[i].item_type ) );
    }
}

