#ifndef include_a570a0cd_752f_492d_8a1d_7b6a2916b806
#define include_a570a0cd_752f_492d_8a1d_7b6a2916b806

/**
	�A�j���[�V�����t�H�[�}�b�g.
	@note �ȈՂ����邪�A�v���O���}����ł��o����l��
	�Œ���̃t�H�[�}�b�g�ɂ��Ă݂�.
*/
struct AnimFormat
{
	int anim_num;	//!< ������.
	int begin_x;	//!< �؂���J�n�ʒu x.
	int begin_y;	//!< �؂���J�n�ʒu y.
	int width;		//!< �؂��蕝.
	int height;		//!< �؂��荂��.
	int draw_frame;	//!< 1 ����\�����钷��.
	int loop_num;	//!< ���[�v��. -1 ���Ɩ���.
};

#endif // include_a570a0cd_752f_492d_8a1d_7b6a2916b806
