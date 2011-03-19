#ifndef save_data_hpp
#define save_data_hpp

#include "Item.hpp"

/**
    �Z�[�u�f�[�^�̌^.
*/
struct SaveData
{
public:
    SaveData();
    void Save();
    void Load();

public:
    int m_item[ItemType_Num];
    int m_total_break;
    int m_max_break;
};

/**
    �Z�[�u�f�[�^.
    @note �V���v���ɃO���[�o���ϐ��Ŏ���.
*/
extern SaveData gSaveData;

#endif // save_data_hpp

