#include "Draw.hpp"

#include "Singleton/SingletonImageLoader.hpp"

void DrawTexture( Vector2 const& pos, ImageType image_type )
{
    DrawGraph(
        static_cast<int>(pos.x), static_cast<int>(pos.y),
        ImageHandleOf( image_type ), TRUE );
}

void DrawTexture( Vector2 const& pos, ImageType image_type, double scale, double angle )
{
    DrawRotaGraph(
        static_cast<int>(pos.x), static_cast<int>(pos.y),
        scale, angle,
        ImageHandleOf( image_type ), TRUE, FALSE );
}

