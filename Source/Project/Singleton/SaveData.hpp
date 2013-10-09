#ifndef save_data_hpp
#define save_data_hpp

#include "Project/Item/ItemInfo.hpp"

struct Player
{
    static int const ItemMax = 100;
    ItemInfo item_list[ItemMax];
};

/**
    �Z�[�u�f�[�^�̌^.
*/
struct SaveData
{
public:
    SaveData();
    ~SaveData();
    void Save();
    void Load();

public:
    Player mPlayer;
};

/**
    �Z�[�u�f�[�^.
    @note �V���v���ɃO���[�o���ϐ��Ŏ���.
*/
extern SaveData gSaveData;

#endif // save_data_hpp

