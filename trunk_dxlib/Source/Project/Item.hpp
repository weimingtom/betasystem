#ifndef item_hpp
#define item_hpp

/**
    �A�C�e���̎��.
*/
enum ItemType
{
    ItemType_Meet,
	ItemType_Water,
    
    ItemType_Num,
};

/**
    �A�C�e�����̎擾.
*/
char const* NameOf( ItemType type );

#endif //item_hpp

