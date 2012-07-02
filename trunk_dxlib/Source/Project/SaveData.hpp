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
    static int const ItemBagSize = 8;
    int m_item[ItemBagSize];
    int m_total_break;
    int m_max_break;
    int m_current_stage;
    int m_player_hp;
    int m_player_mp;
    int m_player_exp;
    int m_player_level;
    int m_selected_stage;
};

/**
    �Z�[�u�f�[�^.
    @note �V���v���ɃO���[�o���ϐ��Ŏ���.
*/
extern SaveData gSaveData;

#endif // save_data_hpp

