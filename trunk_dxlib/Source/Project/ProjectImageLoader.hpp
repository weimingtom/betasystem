#ifndef include_b927764f_14d7_4d98_b1ae_73828a6b6191
#define include_b927764f_14d7_4d98_b1ae_73828a6b6191
/** @file
    プロジェクト専用 ImageLoader の生成.
    @note   ファイル名が素直に "ImageLoader" でない理由は、
            同名のオブジェクトファイルが衝突するのを回避するため.
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

