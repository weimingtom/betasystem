#ifndef include_79f11eca_7022_4d7f_96a5_8d7f678dbe46
#define include_79f11eca_7022_4d7f_96a5_8d7f678dbe46

#include "System/AnimFormat.hpp"
#include "System/Vector2.hpp"

/**
	�A�j���[�V��������e�N�X�`������������N���X.
*/
class AnimTexture
{
public:
	/**
		@param image_handle �\������摜�̃n���h��.
		@param anim_data �A�j���[�V�����f�[�^.
	*/
	AnimTexture( int image_handle, AnimFormat const& anim_data );
	~AnimTexture(){}
	
public:
	/**
		�X�V����.
	*/
	void Update();
	/**
		�`�揈��.
	*/
	void Draw( Vector2 const& camera_pos ) const;
	/**
		�\���ʒu�̐ݒ�.
	*/
	void Set( Vector2 const& pos ){ m_pos = pos; }
	/**
		�A�j���[�V�����̐؂�ւ�.
	*/
	void Set( AnimFormat const& anim_data );

private:
    int m_image_handle;
	int m_frame;		//!< �t���[���J�E���g.
	int m_current_index;	//!< ���\������C���f�b�N�X.
	int m_remain_loop;	//!< �c�胋�[�v��.
	Vector2 m_pos;		//!< �\���ʒu.
    AnimFormat m_anim_data; //!< ���̃A�j���f�[�^.
};

#endif //include_79f11eca_7022_4d7f_96a5_8d7f678dbe46

