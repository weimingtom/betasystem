#ifndef draw_hpp
#define draw_hpp

#include "System/Vector2.hpp"
#include "Singleton/SingletonImageLoader.hpp"

/**
    �摜�`��.
*/
void DrawTexture( Vector2 const& pos, ImageType image_type );

void DrawTexture( Vector2 const& pos, ImageType image_type, double scale, double angle = 0.0f );

//�e�N�X�`���̕����`��
void DrawPartOfTexture( ImageType image_type, Vector2 const& pos, Vector2 const& src_pos, Vector2 const& src_size );

#endif //draw_hpp

