#ifndef include_d1df1b84_ffb8_489d_9781_f028508ad404
#define include_d1df1b84_ffb8_489d_9781_f028508ad404

#include "System/CollisionObject.hpp"
#include "Project/CharacterStatus.hpp"
class Vector2;

class Enemy : public CollisionObject
{
public:
    Enemy(
        Vector2 pos ,
        Vector2 size ,
        int image_handle ,
        CharacterStatus status );
public:
    void Draw() const;
    CharacterStatus StatusOf() const { return m_status; }
    
private:
    int const m_image_handle;
    CharacterStatus m_status;
};

#endif

