#include "SingletonImageLoader.hpp"

#include <memory>

/**
	Žg—p‚·‚é‰æ‘œ–¼.
*/
char const* const image_name[ ImageType_Num ] =
{
    "Resource/BG_Forest.png",
    "Resource/Player.png",
    "Resource/Enemy.png",
    "Resource/Stand.png",
    "Resource/GameEnd.png",
    "Resource/Title.png",
    "Resource/Explain.png",
    "Resource/Result.png",
    "Resource/Gauge.png",
    "Resource/Cutin.png",
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

