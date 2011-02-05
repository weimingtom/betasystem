#include "SingletonImageLoader.hpp"

#include <memory>
#include "DxLibWrapper/ImageLoader.hpp"

/**
	Žg—p‚·‚é‰æ‘œ–¼.
*/
char const* const image_name[ ImageType_Num ] =
{
    "Resource/Image.png",
    "Resource/BG_RedForest.png",
    "Resource/Player.png",
    "Resource/Enemy.png",
    "Resource/sword.png",
    "Resource/magic.png",
    "Resource/shield.png",
    "Resource/icon_RunAway.png",
    "Resource/RunAway.png",
    "Resource/Camp.png",
    "Resource/GameOver.png",
    "Resource/Player_Guard.png",
};


namespace SingletonImageLoader
{
	std::auto_ptr<ImageLoader> instance;

	void Init()
	{
		instance.reset( new_ImageLoader( image_name , ImageType_Num ) );
		instance->Load();
	}
	
	ImageLoader* Get()
	{
		return instance.get();
	}
	
	void Release()
	{
	    instance.reset(0);
	}
}

char const* NameOf( ImageType type )
{
	return image_name[type];
}

