#include "DxLibWrapper/Graphics.hpp"

#include "DxLib.h"

/**
    ���ߐF�𖳌��ɂ���@��Ȃ��̂ŁA
    ���b�v���Ĉ��������炷.
*/
void DrawTexture( int x , int y , int image_handle )
{
    DrawGraph( x , y , image_handle , TRUE );
}

void DrawTexture( Vector2 const& pos , int image_handle )
{
    DrawTexture( static_cast<int>(pos.x) , static_cast<int>(pos.y) , image_handle );
}

