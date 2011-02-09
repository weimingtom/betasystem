#include "SingletonSoundLoader.hpp"

#include <memory>

/**
    �v���W�F�N�g�Ŏg�p����T�E���h�t�@�C�����ꗗ.
*/
char const* const sound_list[ SoundType_Num ] =
{
    "Resource/mast.mp3",
    "Resource/se.wav",
};

namespace
{
    /**
        �T�E���h�t�@�C�����ꗗ�� StringList �ŕԂ�.
    */
	StringList SoundFileList()
	{
	    StringList result;
	    for( int i = 0 ; i < SoundType_Num ; i++ )
	    {
	        result.push_back( sound_list[i] );
	    }
	    return result;
	}
}

String NameOf( SoundType type )
{
    return sound_list[ type ];
}

namespace SingletonSoundLoader
{
	std::auto_ptr< SoundLoader > instance;

	void Init()
	{
		instance.reset( new_SoundLoader( SoundFileList() ) );
		instance->Load();
	}
	
	SoundLoader* Get()
	{
		return instance.get();
	}
	
	void Release()
	{
	    instance.reset(0);
	}
}

