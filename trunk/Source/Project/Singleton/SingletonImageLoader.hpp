#ifndef include_7aee0d29_36ae_42db_814b_3702121f9903
#define include_7aee0d29_36ae_42db_814b_3702121f9903

#include "DxLibWrapper/ImageLoader.hpp"

namespace PrincessImageLoader
{
    /**
    	画像の種類.
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
	    インスタンスの取得.
	*/
	ImageLoader* GetInstance();
	/**
		初期化.
	*/
	void Init();
    /**
        開放処理.
        Dxlibの開放処理タイミングの都合で作成.
    */
    void Release();
    /**
        イメージハンドル取得.
    */
    int ImageHandleOf( ImageType type );
    /**
        ソフトイメージハンドルの取得.
    */
    int SoftImageHandleOf( ImageType type );

	//=====================
	//デバッグ用.
	//=====================
    /**
    	ファイル名の取得.
    */
    char const* NameOf( ImageType type );

} // namespace PrincessImageLoader


#endif //include_7aee0d29_36ae_42db_814b_3702121f9903

