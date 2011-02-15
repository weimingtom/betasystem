#ifndef include_6227f8ae_11de_44fc_ae49_2133fed65c60
#define include_6227f8ae_11de_44fc_ae49_2133fed65c60

/**
	セーブ情報をまとめた構造体.
*/
struct SaveData
{
public:
	/**
		セーブする.
	*/
	void Save();
	/**
		ロードする.
	*/
	void Load();
public:
	int hoge;	//中身は未実装.
};

#endif

