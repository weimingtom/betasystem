#ifndef include_b927764f_14d7_4d98_b1ae_73828a6b6191
#define include_b927764f_14d7_4d98_b1ae_73828a6b6191
/** @file
    �v���W�F�N�g��p ImageLoader �̐���.
    @note   �t�@�C�������f���� "ImageLoader" �łȂ����R�́A
            �����̃I�u�W�F�N�g�t�@�C�����Փ˂���̂�������邽��.
*/
class ImageLoader;

enum ImageType
{
    ImageType_Forest,
    ImageType_Player,
    ImageType_Enemy,
    ImageType_Sword,
    ImageType_Magic,
    ImageType_Shield,
    ImageType_Num,
};

char const* NameOf( ImageType type );

ImageLoader* new_ImageLoader();

#endif

