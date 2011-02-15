#ifndef include_d1df1b84_ffb8_489d_9781_f028508ad404
#define include_d1df1b84_ffb8_489d_9781_f028508ad404

#include "System/Vector2.hpp"
#include "Project/Draw.hpp"

/**
	敵クラス.
*/
class Enemy
{
public:
	/**
		コンストラクタ.
	*/
    Enemy();
	~Enemy(){}
public:
	/**
		更新処理.
	*/
	void Update();
	/**
		描画.
	*/
    void Draw( Vector2 camera_pos ) const;
    /**
        位置の設定.
    */
    void SetPosition( Vector2 pos ){ m_pos = pos; }
    /**
        位置の取得.
    */
    Vector2 Position() const { return m_pos; }
    /**
    	速度の設定.
    */
    void SetSpeed( Vector2 speed ){ m_speed = speed; }
    /**
    	生死の設定.
    */
    void SetAlive( bool is_alive ){ m_is_alive = is_alive; }
    /**
        生死の取得.
    */
    bool IsAlive() const { return m_is_alive; }
	
private:
	Vector2 m_pos;
	Vector2 m_speed;
	bool m_is_alive;
};

#endif

