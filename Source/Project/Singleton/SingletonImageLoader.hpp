#ifndef include_7aee0d29_36ae_42db_814b_3702121f9903
#define include_7aee0d29_36ae_42db_814b_3702121f9903

#include "DxLibWrapper/ImageLoader.hpp"

namespace PrincessImageLoader
{
    /**
    	�摜�̎��.
    */
    enum ImageType
    {
        ImageType_Map,
        ImageType_Map2,
        ImageType_Shadow,
        ImageType_Avater,
        ImageType_DebugTop,
        ImageType_Enemy,
        ImageType_Shot,
        ImageType_Num,
    };
	/**
	    �C���X�^���X�̎擾.
	*/
	ImageLoader* GetInstance();
	/**
		������.
	*/
	void Init();
    /**
        �J������.
        Dxlib�̊J�������^�C�~���O�̓s���ō쐬.
    */
    void Release();
    /**
        �C���[�W�n���h���擾.
    */
    int ImageHandleOf( ImageType type );
    /**
        �\�t�g�C���[�W�n���h���̎擾.
    */
    int SoftImageHandleOf( ImageType type );

	//=====================
	//�f�o�b�O�p.
	//=====================
    /**
    	�t�@�C�����̎擾.
    */
    char const* NameOf( ImageType type );

} // namespace PrincessImageLoader


#endif //include_7aee0d29_36ae_42db_814b_3702121f9903

