#ifndef item_hpp
#define item_hpp

/**
    アイテムの種類.
*/
enum ItemType
{
    ItemType_None,
    ItemType_Meet,
    ItemType_GoodMeet,
    ItemType_LifeWater,
    
    ItemType_Num,
};

/**
    アイテム名の取得.
*/
char const* NameOf( ItemType type );

/**
    ドロップ率. 万分率. 1 は現在の貨幣価値に換算すると 1/10000 にあたる.
*/
int DropPamiriado( ItemType );

#endif //item_hpp

