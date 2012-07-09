#ifndef include_d1df1b84_ffb8_489d_9781_f028508ad404
#define include_d1df1b84_ffb8_489d_9781_f028508ad404

#include <memory>
#include "System/Vector2.hpp"
#include "Project/Draw.hpp"
#include "DxLibWrapper/AnimTexture.hpp"
#include "Project/ManaType.hpp"

/**
	�G�N���X.
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
        �R���X�g���N�^.
        @param type ��������G�̎��.
    */
    Enemy( Type type );
	~Enemy(){}
public:
	/**
		�X�V����.
	*/
	void Update();
	/**
		�`��.
	*/
    void Draw( Vector2 camera_pos ) const;
    /**
        �ʒu�̐ݒ�.
    */
    void SetPosition( Vector2 pos );
    /**
        �ʒu�̎擾.
    */
    Vector2 Position() const { return m_pos; }
    /**
    	���x�̐ݒ�.
    */
    void SetSpeed( Vector2 speed ){ m_speed = speed; }
    /**
    	�����̐ݒ�.
    */
    void SetAlive( bool is_alive ){ m_is_alive = is_alive; }
    /**
        �����̎擾.
    */
    bool IsAlive() const { return m_is_alive; }
    /**
        HP �̎擾.
    */
    int GetHP() const{ return m_hp; }
    /**
        �o���l�̎擾.
    */
    int GetExp() const{ return m_exp; }
    /**
        �\�����邩�ǂ���.
    */
    bool IsVisible() const { return m_is_visible; }
    /**
        ����.
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

