#include "DxLibWrapper/Graphics.hpp"

#include "DxLib.h"

void DrawTexture( Vector2 const& pos , int image_handle )
{
    DrawGraph( static_cast<int>(pos.x), static_cast<int>(pos.y),image_handle, TRUE);
}

