#include "Draw.hpp"

#include "DxLibWrapper/ImageLoader.hpp"
#include "DxLibWrapper/Graphics.hpp"
#include "System/Vector2.hpp"

void DrawTexture( int x, int y, ImageType image_type )
{
    DrawGraph( x, y, SingletonImageLoader::Get()->ImageHandleOf( NameOf( image_type ) ) );
}

void DrawTexture( Vector2 const& pos, ImageType image_type )
{
	DrawTexture( static_cast<int>(pos.x), static_cast<int>(pos.y), image_type );
}



