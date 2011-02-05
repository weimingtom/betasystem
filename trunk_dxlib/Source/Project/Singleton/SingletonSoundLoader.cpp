#include "SingletonSoundLoader.hpp"

#include "DxLibWrapper/SoundLoader.hpp"
#include <memory>

char const* const sound_list[ SoundType_Num ] =
{
    "Resource/mast.mp3",
    "Resource/poi.wav",
    "Resource/pi.wav",
    "Resource/poire.wav",
    "Resource/Short_attack1.wav",
    "Resource/suiteki.wav",
    "Resource/Extracting_sword.wav",
};

namespace
{
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

