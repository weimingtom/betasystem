#include "SingletonImageLoader.hpp"

#include <memory>

/**
	�g�p����摜��.
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

char const* NameOf( ImageType type )
{
	return image_name[type];
}

std::auto_ptr<ImageLoader> gImageLoader;

namespace SingletonImageLoader
{

	void Init()
	{
		gImageLoader.reset( new_ImageLoader( image_name , ImageType_Num ) );
		gImageLoader->Load();
	}
	
	ImageLoader* Get()
	{
		return gImageLoader.get();
	}
	
	void Release()
	{
	    gImageLoader.reset(0);
	}
}

int ImageHandleOf( ImageType type )
{
    return gImageLoader->ImageHandleOf( NameOf(type) );
}

