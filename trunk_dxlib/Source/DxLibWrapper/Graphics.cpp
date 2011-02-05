#include "DxLibWrapper/Graphics.hpp"

#include "DxLib.h"

/**
    透過色を無効にする機会がないので、
    ラップして引数を減らす.
*/
void DrawTexture( int x , int y , int image_handle )
{
    DrawGraph( x , y , image_handle , TRUE );
}

void DrawTexture( Vector2 const& pos , int image_handle )
{
    DrawTexture( static_cast<int>(pos.x) , static_cast<int>(pos.y) , image_handle );
}

