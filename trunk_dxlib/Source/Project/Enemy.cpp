#include "Project/Enemy.hpp"
#include "DxLibWrapper/Graphics.hpp"

Enemy::Enemy(
    Vector2 pos ,
    Vector2 size ,
    int image_handle ,
    CharacterStatus status )
 : CollisionObject( pos , size )
 , m_status( status )
 , m_image_handle( image_handle )
{
}

void Enemy::Draw() const
{
    DrawTexture( m_pos , m_image_handle );
    DrawCollision();
}


