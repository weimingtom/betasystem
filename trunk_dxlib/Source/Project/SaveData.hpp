#ifndef save_data_hpp
#define save_data_hpp

#include "Item.hpp"

/**
    �Z�[�u�f�[�^�̌^.
*/
struct SaveData{
    int m_item[ItemType_Num];
    int m_total_break;
    /**
        ������.
    */
    SaveData(){
        for( int i = 0 ; i < ItemType_Num ; i ++ ){
            m_item[i] = 0;
        }
        m_total_break = 0;
    }
};

/**
    �Z�[�u�f�[�^.
    @note �V���v���ɃO���[�o���ϐ��Ŏ���.
*/
extern SaveData gSaveData;

#endif // save_data_hpp

