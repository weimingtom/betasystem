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
    "Resource/Enemy2.png",
    "Resource/Enemy3.png",
    "Resource/GameEnd.png",
    "Resource/Title.png",
    "Resource/ItemFrame.png",
    "Resource/ItemList.png",
    "Resource/stand.png",
    "Resource/stand_slime.png",
    "Resource/box.png",
    "Resource/BattleFrame.png",
    "Resource/avater.png",
    "Resource/dummy.png",
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

