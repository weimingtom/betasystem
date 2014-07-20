#include "SingletonImageLoader.hpp"

#include <memory>
#include "DxLibWrapper/ImageLoader.hpp"


namespace ProjectImageLoader{

    //! シングルトンインスタンス.
    std::auto_ptr<ImageLoader> gImageLoader;

    /**
    	使用する画像名.
    */
    char const* const image_name[ ImageType_Num ] =
    {
        "Resource/map.png",
        "Resource/shadow.png",
        "Resource/Avater.bmp",
        "Resource/debug_logo.png",
        "Resource/enemy.png",
    };

    char const* NameOf( ImageType type )
    {
    	return image_name[type];
    }

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

    int ImageHandleOf( ImageType type )
    {
        return gImageLoader->ImageHandleOf( NameOf(type) );
    }

    int SoftImageHandleOf( ImageType type )
    {
        return gImageLoader->SoftImageHandleOf( NameOf(type) );
    }

} // namespace ProjectImageLoader

