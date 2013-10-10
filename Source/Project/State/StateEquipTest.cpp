#include "StateEquipTest.hpp"

#include "Project/Singleton/SaveData.hpp"
#include "System/Range.hpp"
#include "System/ArraySize.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"

StateEquipTest::StateEquipTest()
 : mIndex(0)
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
    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){
        --mIndex;
    }
    else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){
        ++mIndex;
    }
    mIndex = Clamp( 0, mIndex, Player::ItemMax - 1 );
    
    //決定で装備アイテムなら装備.
    if( KeyInput()->IsTrig( InputKey::Type_Enter ) ) 
    {
        ItemInfo const current_item = gSaveData.mPlayer.mItemList[mIndex];
        //選択したものが装備なら
        if( current_item.IsEquip() ){
            //指定アイテムと、装備箇所のアイテムとスワップ
            ItemInfo const swap_temp = gSaveData.mPlayer.mEquipList[current_item.equip_pos];
            gSaveData.mPlayer.mEquipList[current_item.equip_pos] = current_item;
            gSaveData.mPlayer.mItemList[mIndex] = swap_temp;
        }
    }
}

void StateEquipTest::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "装備テスト");
    
    DrawFormatString( 0 , 50+mIndex*15 , GetColor(0,255,0) , "→");
    //所持アイテムの表示.
    for(int i = 0 ; i < Player::ItemMax ; i++ ){
        DrawFormatString( 50 , 50 + i*15 , GetColor(0,255,0) , NameOf( gSaveData.mPlayer.mItemList[i].item_type ) );
    }
    //装備の表示
    for( int i = 0 ; i < ARRAY_SIZE( gSaveData.mPlayer.mEquipList ) ; i++ ){
        DrawFormatString( 150 , 50 + i*15 , GetColor(0,255,0) , NameOf( gSaveData.mPlayer.mEquipList[i].item_type ) );
    }
}

