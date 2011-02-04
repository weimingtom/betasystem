#ifndef include_7aee0d29_36ae_42db_814b_3702121f9903
#define include_7aee0d29_36ae_42db_814b_3702121f9903

class ImageLoader;

/**
	使用する
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
    ImageType_Num,
};

/**
	ファイル名の取得.
*/
char const* NameOf( ImageType type );

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
}


#endif //include_7aee0d29_36ae_42db_814b_3702121f9903

