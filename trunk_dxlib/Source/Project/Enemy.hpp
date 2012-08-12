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
        HP の取得.
    */
    int GetHP() const{ return m_hp; }
    /**
        経験値の取得.
    */
    int GetExp() const{ return m_exp; }
	
private:
    int m_hp;
    int m_exp;
    int m_attack;
    int m_speed;
    int m_level;
	Vector2 m_pos;
	std::auto_ptr<AnimTexture> m_anim_tex;
};

#endif

