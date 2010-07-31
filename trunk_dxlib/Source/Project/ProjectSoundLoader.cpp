#include "Project/ProjectSoundLoader.hpp"

char const* const sound_list[ SoundType_Num ] =
{
    "Resource/mast.mp3",
    "Resource/poi.wav",
};

String NameOf( SoundType type )
{
    return sound_list[ type ];
}

StringList SoundFileList()
{
    StringList result;
    for( int i = 0 ; i < SoundType_Num ; i++ )
    {
        result.push_back( sound_list[i] );
    }
    return result;
}

