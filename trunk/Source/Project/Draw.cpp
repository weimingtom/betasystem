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

void DrawPartOfTexture( ImageType image_type, Vector2 const& pos, Vector2 const& src_pos, Vector2 const& src_size )
{
	DrawRectGraph(
		static_cast<int>(pos.x),static_cast<int>(pos.y),
		static_cast<int>(src_pos.x),static_cast<int>(src_pos.y),
		static_cast<int>(src_size.x),static_cast<int>(src_size.y),
		ImageHandleOf(image_type),TRUE,FALSE);
}

