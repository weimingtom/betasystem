#ifndef include_beae02af_6d26_467d_bbed_d53d09d9ef51
#define include_beae02af_6d26_467d_bbed_d53d09d9ef51

#include <string>
#include <vector>
typedef std::vector< std::string > StringList;

/**
    �T�E���h�Ǘ�.
*/
class SoundLoader
{
public:
    /**
        �����֐�.
    */
    friend SoundLoader* new_SoundLoader( StringList file_name_list );
    virtual ~SoundLoader(){}
    
public:
    /**
        �������A�̃��[�h.
    */
    virtual void Load() = 0;
    
    /**
        �Đ�.
    */
    virtual void Play( std::string file_name ) = 0;
    
private:
    class Impl;
};

SoundLoader* new_SoundLoader( StringList file_name_list );

#endif

