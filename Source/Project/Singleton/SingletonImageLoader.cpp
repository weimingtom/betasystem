#include "SingletonImageLoader.hpp"

#include <memory>
#include "DxLibWrapper/ImageLoader.hpp"


namespace ProjectImageLoader{

    //! �V���O���g���C���X�^���X.
    std::auto_ptr<ImageLoader> gImageLoader;

    /**
    	�g�p����摜��.
    */
    char const* const image_name[ ImageType_Num ] =
    {
        "Resource/BG_Forest.png",
        "Resource/Koyaku.png",
        "Resource/Avater.bmp",
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

} // namespace ProjectImageLoader

