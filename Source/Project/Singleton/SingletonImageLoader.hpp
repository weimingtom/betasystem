#ifndef include_7aee0d29_36ae_42db_814b_3702121f9903
#define include_7aee0d29_36ae_42db_814b_3702121f9903

#include "DxLibWrapper/ImageLoader.hpp"


namespace ProjectImageLoader{

    /**
    	使用する画像.
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
    	ファイル名の取得.
    */
    char const* NameOf( ImageType type );

	/**
		初期化.
	*/
	void Init();
	/**
	    インスタンスの取得.
	*/
	ImageLoader* GetInstance();
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

} // namespace ProjectImageLoader


#endif //include_7aee0d29_36ae_42db_814b_3702121f9903

