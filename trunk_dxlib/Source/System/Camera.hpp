#ifndef include_camera_hpp
#define include_camera_hpp

#include "System/Vector2.hpp"
/**
    カメラの役割をするクラス.
*/
class Camera
{
public:
    /**
        座標の設定.
    */
    void SetPos( Vector2 pos ){ m_pos = pos; }
    /**
        座標の取得.
    */
    Vector2 Position() const{ return m_pos; }
    
private:
    Vector2 m_pos;
};

#endif

