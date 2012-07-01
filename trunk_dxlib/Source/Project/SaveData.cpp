#include "SaveData.hpp"

#include <assert.h>


SaveData gSaveData;

SaveData::SaveData()
{
    for( int i = 0 ; i < ItemBagSize ; i ++ ){
        m_item[i] = 0;
    }
    m_total_break = 0;
    m_max_break = 0;
    m_current_stage = 0;
    m_player_hp = 120;
    m_player_mp = 100;
}

void SaveData::Save()
{
	FILE* fp;
	int const err = fopen_s( &fp, "SaveFile.bin", "wb");
	if( err != 0 ){ assert(false); }

	int const write_num = 1;
    int const ret = fwrite( &gSaveData, sizeof(gSaveData), write_num, fp);
    assert( ret >= write_num );
	fclose(fp);
}

void SaveData::Load()
{
    FILE* fp;
    int const read_num = 1;

    //�J���Ȃ��ꍇ�̓X���[
    if( fopen_s( &fp, "SaveFile.bin", "rb") != 0 ){
        return;
    }

    //�ǂݍ��ݎ��s���X���[
    SaveData save_data;
    int const ret = fread(&save_data, sizeof(gSaveData), read_num, fp);
	fclose(fp);
    if( ret < read_num ){
        return;
    }
    
    gSaveData = save_data;
}

