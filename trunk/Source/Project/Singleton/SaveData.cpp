#include "SaveData.hpp"

#include <assert.h>

SaveData gSaveData;

SaveData::SaveData()
{
}

SaveData::~SaveData()
{
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

    //開けない場合はスルー
    if( fopen_s( &fp, "SaveFile.bin", "rb") != 0 ){
        return;
    }

    //読み込み失敗もスルー
    SaveData save_data;
    int const ret = fread(&save_data, sizeof(gSaveData), read_num, fp);
	fclose(fp);
    if( ret < read_num ){
        return;
    }
    
    gSaveData = save_data;
}

