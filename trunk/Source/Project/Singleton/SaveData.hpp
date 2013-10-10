#ifndef save_data_hpp
#define save_data_hpp

/**
    セーブデータの型.
*/
struct SaveData
{
public:
    SaveData();
    ~SaveData();
    void Save();
    void Load();
};

/**
    セーブデータ.
    @note シンプルにグローバル変数で持つ.
*/
extern SaveData gSaveData;

#endif // save_data_hpp

