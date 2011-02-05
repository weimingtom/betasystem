#ifndef draw_hpp
#define draw_hpp

class Vector2;
#include "Singleton/SingletonImageLoader.hpp"

/**
    ‰æ‘œ•`‰æ.
*/
void DrawTexture( int x, int y, ImageType image_type );

void DrawTexture( Vector2 const& pos, ImageType image_type );



#endif