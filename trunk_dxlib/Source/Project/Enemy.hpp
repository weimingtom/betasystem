#ifndef include_d1df1b84_ffb8_489d_9781_f028508ad404
#define include_d1df1b84_ffb8_489d_9781_f028508ad404

#include <memory>
#include "System/Vector2.hpp"
#include "Project/Draw.hpp"
#include "DxLibWrapper/AnimTexture.hpp"
#include "Project/ManaType.hpp"

/**
	敵クラス.
*/
class Enemy
{
public:
    enum Type{
        Type_GreenSlime,
        Type_RedSlime,
        Type_SteelSlime,
        Type_Num,
    };
public:
    /**
        コンストラクタ.
        @param type 生成する敵の種類.
    */
    Enemy( Type type );
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
    void SetPosition( Vector2 pos );
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
    /**
        HP の取得.
    */
    int GetHP() const{ return m_hp; }
    /**
        経験値の取得.
    */
    int GetExp() const{ return m_exp; }
    /**
        表示するかどうか.
    */
    bool IsVisible() const { return m_is_visible; }
    /**
        属性.
    */
	ManaType GetManaType() const{ return m_mana_type; }
	
private:
    int m_hp;
    int m_exp;
	Vector2 m_pos;
	Vector2 m_speed;
	bool m_is_alive;
	std::auto_ptr<AnimTexture> m_anim_tex;
	bool m_is_visible;
	int m_frame;
	ManaType m_mana_type;
};

#endif

