#ifndef include_7aee0d29_36ae_42db_814b_3702121f9903
#define include_7aee0d29_36ae_42db_814b_3702121f9903

class ImageLoader;

/**
	�g�p����
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
	�t�@�C�����̎擾.
*/
char const* NameOf( ImageType type );

namespace SingletonImageLoader
{
	/**
		������.
	*/
	void Init();
	/**
		�C���X�^���X�̎擾.
	*/
	ImageLoader* Get();
}


#endif //include_7aee0d29_36ae_42db_814b_3702121f9903

