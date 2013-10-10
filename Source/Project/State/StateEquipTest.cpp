#include "StateEquipTest.hpp"

#include "Project/Singleton/SaveData.hpp"
#include "Project/Singleton/PlayerParam.hpp"
#include "System/Range.hpp"
#include "System/ArraySize.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"

StateEquipTest::StateEquipTest()
 : mIndex(0)
 , mAvater( new Avater( gPlayerParam.mEquipList ) )
{
    //プレイヤーにいくつかアイテム持たせる。
    for( int i = 0 ; i < ItemType_Num ; i++ ){
        gPlayerParam.mItemList[i] = ItemInfoOf(static_cast<ItemType>(i));
        gPlayerParam.mItemList[i].color = GetRand(INT_MAX);
    }
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
    mIndex = Clamp( 0, mIndex, PlayerParam::ItemMax - 1 );
    
    //決定で装備アイテムなら装備.
    if( KeyInput()->IsTrig( InputKey::Type_Enter ) ) 
    {
        ItemInfo const current_item = gPlayerParam.mItemList[mIndex];
        //選択したものが装備なら
        if( current_item.IsEquip() ){
            //指定アイテムと、装備箇所のアイテムとスワップ
            ItemInfo const swap_temp = gPlayerParam.mEquipList[current_item.equip_pos];
            gPlayerParam.mEquipList[current_item.equip_pos] = current_item;
            gPlayerParam.mItemList[mIndex] = swap_temp;
            mAvater.reset( new Avater(gPlayerParam.mEquipList) );
        }
        
    }
}

void StateEquipTest::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "装備テスト");
    
    DrawFormatString( 0 , 50+mIndex*15 , GetColor(0,255,0) , "→");
    //所持アイテムの表示.
    for(int i = 0 ; i < PlayerParam::ItemMax ; i++ ){
        DrawFormatString( 50 , 50 + i*15 , GetColor(0,255,0) , NameOf( gPlayerParam.mItemList[i].item_type ) );
    }
    //装備の表示
    for( int i = 0 ; i < ARRAY_SIZE( gPlayerParam.mEquipList ) ; i++ ){
        DrawFormatString( 150 , 50 + i*15 , GetColor(0,255,0) , NameOf( gPlayerParam.mEquipList[i].item_type ) );
    }
    mAvater->Draw(300,100);
}

