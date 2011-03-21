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
    ドロップ率. １万分率. 1 は 1/10000 にあたる.
*/
int DropPamiriado( ItemType );

#endif //item_hpp

