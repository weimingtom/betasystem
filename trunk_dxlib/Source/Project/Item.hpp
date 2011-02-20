#ifndef item_hpp
#define item_hpp

/**
    アイテムの種類.
*/
enum ItemType
{
    ItemType_Meet,
	ItemType_Water,
    
    ItemType_Num,
};

/**
    アイテム名の取得.
*/
char const* NameOf( ItemType type );

#endif //item_hpp

