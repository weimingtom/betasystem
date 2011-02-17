#include "Draw.hpp"

#include "DxLib.h"

void DrawTexture( Vector2 const& pos, ImageType image_type )
{
    DrawGraph(
        static_cast<int>(pos.x), static_cast<int>(pos.y),
        SingletonImageLoader::Get()->ImageHandleOf( NameOf( image_type ) ), TRUE );
}

