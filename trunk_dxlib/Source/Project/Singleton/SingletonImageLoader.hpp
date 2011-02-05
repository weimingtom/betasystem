#ifndef include_7aee0d29_36ae_42db_814b_3702121f9903
#define include_7aee0d29_36ae_42db_814b_3702121f9903

#include "DxLibWrapper/ImageLoader.hpp"

/**
	使用する画像.
*/
enum ImageType
{
    ImageType_Forest,
    ImageType_RedForest,
    ImageType_Player,
    ImageType_Enemy,
    ImageType_Sword,
    ImageType_Magic,
    ImageType_Shield,
    ImageType_IconRunAway,
    ImageType_RunAway,
    ImageType_Camp,
    ImageType_GameOver,
    ImageType_Player_Guard,
    ImageType_Stand,
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
		インスタンスの取得.
	*/
	ImageLoader* Get();
    /**
        開放処理.
    */
    void Release();
}

#endif //include_7aee0d29_36ae_42db_814b_3702121f9903

