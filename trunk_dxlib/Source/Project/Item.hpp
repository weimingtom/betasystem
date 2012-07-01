#ifndef item_hpp
#define item_hpp

/**
    �A�C�e���̎��.
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
    �A�C�e�����̎擾.
*/
char const* NameOf( ItemType type );

/**
    �h���b�v��. ������. 1 �͌��݂̉ݕ����l�Ɋ��Z����� 1/10000 �ɂ�����.
*/
int DropPamiriado( ItemType );

#endif //item_hpp

