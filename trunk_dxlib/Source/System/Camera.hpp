#ifndef include_camera_hpp
#define include_camera_hpp

#include "System/Vector2.hpp"
/**
    �J�����̖���������N���X.
*/
class Camera
{
public:
    /**
        ���W�̐ݒ�.
    */
    void SetPos( Vector2 pos ){ m_pos = pos; }
    /**
        ���W�̎擾.
    */
    Vector2 Position() const{ return m_pos; }
    
private:
    Vector2 m_pos;
};

#endif

