#include "PlayerLife.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "Project/Draw.hpp"

PlayerLife::PlayerLife( int life_num )
 : mLifeNum(life_num)
{
}

PlayerLife::~PlayerLife()
{
}

void PlayerLife::Draw() const
{
/*
	int x = 0;
    int y = 50;
    int width = 70;
    DrawTexture( Vector2(x,y) , ImageType_FaceFrame );
    x+=width;
    for( int i = 0 ; i < mLifeNum; i++ ){
        DrawTexture( Vector2(x+i*width,y) , ImageType_Face );
    }
*/
}

