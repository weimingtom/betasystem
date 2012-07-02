#ifndef include_7aee0d29_36ae_42db_814b_3702121f9903
#define include_7aee0d29_36ae_42db_814b_3702121f9903

#include "DxLibWrapper/ImageLoader.hpp"

/**
	使用する画像.
*/
enum ImageType
{
    ImageType_Forest,
    ImageType_Player,
    ImageType_GreenSlime,
    ImageType_RedSlime,
    ImageType_SteelSlime,
    ImageType_GameEnd,
    ImageType_Title,
    ImageType_Explain,
    ImageType_Result,
    ImageType_Cutin,
    ImageType_Number,
    ImageType_ItemFrame,
    ImageType_ItemList,
    ImageType_Face,
    ImageType_FaceFrame,
    ImageType_SwordFrame,
    ImageType_SwordPower,
    ImageType_StandFuriru,
    ImageType_SelectStage1,
    ImageType_SelectStage2,
    ImageType_Dummy,

    ImageType_Num,
};

/**
	ファイル名の取得.
*/
char const* NameOf( ImageType type );

/**
    プロジェクト唯一の ImageLoader.
*/
namespace SingletonImageLoader
{
	/**
		初期化.
	*/
	void Init();
    /**
        開放処理.
    */
    void Release();
}

/**
    イメージハンドル取得.
*/
int ImageHandleOf( ImageType type );

#endif //include_7aee0d29_36ae_42db_814b_3702121f9903

