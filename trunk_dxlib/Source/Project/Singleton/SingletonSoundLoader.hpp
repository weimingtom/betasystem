#ifndef include_9039b86b_bf2b_49ff_86f4_741d42f0e5a9
#define include_9039b86b_bf2b_49ff_86f4_741d42f0e5a9

#include <string>
#include "DxLibWrapper/SoundLoader.hpp"

enum SoundType
{
    SoundType_Mast,
    SoundType_Decide,
    SoundType_OK,
    SoundType_Just,
    SoundType_Item,

    SoundType_Num,
};

typedef std::string String;

String NameOf( SoundType type );

/**
    �v���W�F�N�g�B��� SoundLoader.
*/
namespace SingletonSoundLoader
{
	/**
		������.
	*/
	void Init();
	
	/**
		�C���X�^���X�̎擾.
	*/
	SoundLoader* Get();
	/**
	    �J������.
	*/
	void Release();
}



#endif // include_9039b86b_bf2b_49ff_86f4_741d42f0e5a9

