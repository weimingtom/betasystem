#include "DxLibWrapper/Graphics.hpp"

#include "DxLib.h"
#include "System/Vector2.hpp"

/**
    ���ߐF�𖳌��ɂ���@��Ȃ��̂ŁA
    ���b�v���Ĉ��������炷.
*/
void DrawGraph( int x , int y , int image_handle )
{
    DrawGraph( x , y , image_handle , TRUE );
}

/**
    Vector2 �ł̉摜�`��.
*/
void DrawGraph( Vector2 pos , int image_handle )
{
    DrawGraph( pos.x , pos.y , image_handle );
}

