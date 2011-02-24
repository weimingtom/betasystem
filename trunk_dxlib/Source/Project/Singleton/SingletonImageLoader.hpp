#ifndef include_7aee0d29_36ae_42db_814b_3702121f9903
#define include_7aee0d29_36ae_42db_814b_3702121f9903

#include "DxLibWrapper/ImageLoader.hpp"

/**
	�g�p����摜.
*/
enum ImageType
{
    ImageType_Forest,
    ImageType_Player,
    ImageType_Enemy,
    ImageType_Stand,
    ImageType_GameEnd,
    ImageType_Title,
    ImageType_Explain,
    ImageType_Result,
    ImageType_Gauge,
    ImageType_Cutin,
    ImageType_Cutin2,
    ImageType_Cutin3,
    ImageType_Light,

    ImageType_Num,
};

/**
	�t�@�C�����̎擾.
*/
char const* NameOf( ImageType type );

/**
    �v���W�F�N�g�B��� ImageLoader.
*/
namespace SingletonImageLoader
{
	/**
		������.
	*/
	void Init();
    /**
        �J������.
    */
    void Release();
}

/**
    �C���[�W�n���h���擾.
*/
int ImageHandleOf( ImageType type );

#endif //include_7aee0d29_36ae_42db_814b_3702121f9903

