#ifndef include_9039b86b_bf2b_49ff_86f4_741d42f0e5a9
#define include_9039b86b_bf2b_49ff_86f4_741d42f0e5a9

class SoundLoader;
#include <string>

enum SoundType
{
    SoundType_WorldMap,
    SoundType_Decide,
    SoundType_OnButton,
    SoundType_ReleaseButton,
    SoundType_Attack,
    SoundType_BeginGuard,
    SoundType_SuccessGuard,
    SoundType_Num,
};

typedef std::string String;

String NameOf( SoundType type );

namespace SingletonSoundLoader
{
	/**
		初期化.
	*/
	void Init();
	
	/**
		インスタンスの取得.
	*/
	SoundLoader* Get();
}



#endif // include_9039b86b_bf2b_49ff_86f4_741d42f0e5a9

