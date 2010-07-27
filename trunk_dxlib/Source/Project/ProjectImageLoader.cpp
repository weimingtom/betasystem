#include "Project/ProjectImageLoader.hpp"

#include "DxLibWrapper/ImageLoader.hpp"
#include "System/ArraySize.hpp"

char const* const image_name[ ImageType_Num ] =
{
    "Resource/Image.png",
    "Resource/Player.png",
    "Resource/Enemy.png",
    "Resource/sword.png",
    "Resource/magic.png",
    "Resource/shield.png",
    "Resource/RunAway.png",
};

char const* NameOf( ImageType type )
{
    return image_name[ type ];
}

ImageLoader* new_ImageLoader()
{
    return new_ImageLoader( image_name , ARRAY_SIZE( image_name ) );
}


