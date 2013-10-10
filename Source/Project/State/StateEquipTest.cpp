#include "StateEquipTest.hpp"

#include "Project/Singleton/SaveData.hpp"
#include "System/Range.hpp"
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
}

