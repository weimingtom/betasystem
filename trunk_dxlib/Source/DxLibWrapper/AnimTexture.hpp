#ifndef include_79f11eca_7022_4d7f_96a5_8d7f678dbe46
#define include_79f11eca_7022_4d7f_96a5_8d7f678dbe46

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
	AnimTexture( int image_handle, AnimData const& anim_data );
	~AnimTexture();
	
public:
	/**
		�X�V����.
	*/
	void Update();
	/**
		�`�揈��.
	*/
	void Draw( Vector2 camera_pos ) const;
	/**
		�\���ʒu�̐ݒ�.
	*/
	void Set( Vector2 pos );
	/**
		�A�j���[�V�����̐؂�ւ�.
	*/
	void Set( AnimData const& anim_data );

private:
	int m_frame;		//!< �t���[���J�E���g.
	int m_anim_index;	//!< ���\������C���f�b�N�X.
	int remain_loop;	//!< �c�胋�[�v��.
	Vector2 m_pos;		//!< �\���ʒu.
};

#endif //include_79f11eca_7022_4d7f_96a5_8d7f678dbe46

