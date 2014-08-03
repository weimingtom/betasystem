#include "SingletonImageLoader.hpp"

#include <memory>
#include "DxLibWrapper/ImageLoader.hpp"


namespace PrincessImageLoader{

    //! シングルトンインスタンス.
    std::auto_ptr<ImageLoader> sImageLoader;

    /**
    	使用する画像名.
    */
    char const* const image_name[ ImageType_Num ] =
    {
        "Resource/map.png",
        "Resource/map2.png",
        "Resource/shadow.png",
        "Resource/Avater.bmp",
        "Resource/player.png",
        "Resource/enemy.png",
        "Resource/shot.png",
        "Resource/paricle.png",
    };

    char const* NameOf( ImageType type )
    {
    	return image_name[type];
    }

	void Init()
	{
		sImageLoader.reset( new_ImageLoader( image_name , ImageType_Num ) );
		sImageLoader->Load();
	}
	
	ImageLoader* Get()
	{
		return sImageLoader.get();
	}
	
	void Release()
	{
	    sImageLoader.reset(0);
	}

    int ImageHandleOf( ImageType type )
    {
        return sImageLoader->ImageHandleOf( NameOf(type) );
    }

    int SoftImageHandleOf( ImageType type )
    {
        return sImageLoader->SoftImageHandleOf( NameOf(type) );
    }

} // namespace PrincessImageLoader


