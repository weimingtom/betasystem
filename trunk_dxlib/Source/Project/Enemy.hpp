#ifndef include_d1df1b84_ffb8_489d_9781_f028508ad404
#define include_d1df1b84_ffb8_489d_9781_f028508ad404

#include "System/Vector2.hpp"

/**
	�G�N���X.
*/
class Enemy
{
public:
	/**
		�R���X�g���N�^.
		@param pos �������W.
	*/
    Enemy( Vector2 init_pos );
	~Enemy(){}
public:
	/**
		�X�V����.
	*/
	void Update();
	/**
		�`��.
	*/
    void Draw() const;
    /**
    	���x�̐ݒ�.
    */
    void SetSpeed( Vector2 speed ){ m_speed = speed; }
    /**
    	�����̐ݒ�.
    */
    void SetAlive( bool is_alive ){ m_is_alive = is_alive; }
	
private:
	Vector2 m_pos;
	Vector2 m_speed;
	bool m_is_alive;
};

#endif

