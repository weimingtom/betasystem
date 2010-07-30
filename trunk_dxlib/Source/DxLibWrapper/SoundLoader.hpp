#ifndef include_beae02af_6d26_467d_bbed_d53d09d9ef51
#define include_beae02af_6d26_467d_bbed_d53d09d9ef51

#include <string>
#include <vector>
typedef std::vector< std::string > StringList;

/**
    サウンド管理.
*/
class SoundLoader
{
public:
    /**
        生成関数.
    */
    friend SoundLoader* new_SoundLoader( StringList file_name_list );
    virtual ~SoundLoader(){}
    
public:
    /**
        完了復帰のロード.
    */
    virtual void Load() = 0;
    
    /**
        再生.
    */
    virtual void Play( std::string file_name ) = 0;
    
private:
    class Impl;
};

SoundLoader* new_SoundLoader( StringList file_name_list );

#endif

