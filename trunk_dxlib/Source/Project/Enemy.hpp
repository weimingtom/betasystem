#ifndef include_d1df1b84_ffb8_489d_9781_f028508ad404
#define include_d1df1b84_ffb8_489d_9781_f028508ad404

#include "System/Vector2.hpp"
#include "Project/Draw.hpp"

/**
	�G�N���X.
*/
class Enemy
{
public:
	/**
		�R���X�g���N�^.
	*/
    Enemy();
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
    void SetPosition( Vector2 pos ){ m_pos = pos; }
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
	
private:
	Vector2 m_pos;
	Vector2 m_speed;
	bool m_is_alive;
};

#endif

