#include "SingletonSoundLoader.hpp"

#include <memory>

/**
    プロジェクトで使用するサウンドファイル名一覧.
*/
char const* const sound_list[ SoundType_Num ] =
{
    "Resource/mast.mp3",
    "Resource/se.wav",
};

namespace
{
    /**
        サウンドファイル名一覧を StringList で返す.
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

