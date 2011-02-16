#include "Draw.hpp"

#include "DxLibWrapper/Graphics.hpp"

void DrawTexture( Vector2 const& pos, ImageType image_type )
{
    DrawTexture( pos, SingletonImageLoader::Get()->ImageHandleOf( NameOf( image_type ) ) );
}

