#ifndef include_d1df1b84_ffb8_489d_9781_f028508ad404
#define include_d1df1b84_ffb8_489d_9781_f028508ad404

#include "System/Vector2.hpp"

/**
	敵クラス.
*/
class Enemy
{
public:
	/**
		コンストラクタ.
		@param pos 初期座標.
	*/
    Enemy( Vector2 init_pos );
	~Enemy(){}
public:
	/**
		更新処理.
	*/
	void Update();
	/**
		描画.
	*/
    void Draw() const;
    /**
    	速度の設定.
    */
    void SetSpeed( Vector2 speed ){ m_speed = speed; }
    /**
    	生死の設定.
    */
    void SetAlive( bool is_alive ){ m_is_alive = is_alive; }
	
private:
	Vector2 m_pos;
	Vector2 m_speed;
	bool m_is_alive;
};

#endif

