#include "DxLibWrapper/Graphics.hpp"

#include "DxLib.h"
#include "System/Vector2.hpp"

/**
    透過色を無効にする機会がないので、
    ラップして引数を減らす.
*/
void DrawGraph( int x , int y , int image_handle )
{
    DrawGraph( x , y , image_handle , TRUE );
}

/**
    Vector2 での画像描画.
*/
void DrawGraph( Vector2 pos , int image_handle )
{
    DrawGraph( static_cast<int>(pos.x) , static_cast<int>(pos.y) , image_handle );
}

