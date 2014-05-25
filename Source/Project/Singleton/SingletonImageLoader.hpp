#ifndef include_7aee0d29_36ae_42db_814b_3702121f9903
#define include_7aee0d29_36ae_42db_814b_3702121f9903

#include "DxLibWrapper/ImageLoader.hpp"


namespace ProjectImageLoader{

    /**
    	�g�p����摜.
    */
    enum ImageType
    {
        ImageType_Forest,
        ImageType_Koyaku,
        ImageType_Avater,
        ImageType_DebugTop,
        ImageType_Num,
    };
    /**
    	�t�@�C�����̎擾.
    */
    char const* NameOf( ImageType type );

	/**
		������.
	*/
	void Init();
	/**
	    �C���X�^���X�̎擾.
	*/
	ImageLoader* GetInstance();
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

} // namespace ProjectImageLoader


#endif //include_7aee0d29_36ae_42db_814b_3702121f9903

