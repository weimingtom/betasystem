#ifndef draw_hpp
#define draw_hpp

#include "System/Vector2.hpp"
#include "Singleton/SingletonImageLoader.hpp"

/**
    ‰æ‘œ•`‰æ.
*/
void DrawTexture( Vector2 const& pos, ImageType image_type );

void DrawTexture( Vector2 const& pos, ImageType image_type, double scale, double angle = 0.0f );

#endif //draw_hpp

