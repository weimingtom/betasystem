#ifndef Game_SOURCE_PROJECT_SINGLETON_SINGLETONIMAGELOADER
#define Game_SOURCE_PROJECT_SINGLETON_SINGLETONIMAGELOADER

#include <vector>
#include <string>
#include <map>

typedef std::vector<std::string> ImageNameList;
typedef std::map< std::string , int > ImageMap;

namespace Game
{
	/**
		画像の種類.
	*/
	enum ImageType
	{
//	    ImageType_Map,
//	    ImageType_Map2,
//	    ImageType_Shadow,
//	    ImageType_Avater,
	    ImageType_DebugTop,
//	    ImageType_Enemy,
//	    ImageType_Shot,
//	    ImageType_Particle,
//	    ImageType_MapObject,
//	    ImageType_Item,
	    ImageType_Num,
	};

	class ImageLoader
	{
	public:
		/**
		    インスタンスの取得.
		*/
		static ImageLoader* GetInstance();

		/**
			初期化.
		*/
		static void Initialize();

	    /**
	        開放処理.
	    */
	    static void Finalize();
	private:
		ImageLoader();

	public:
		~ImageLoader();

	public:
	    /**
	        イメージハンドル取得.
	    */
	    int ImageHandleOf( ImageType type );

		
	    /**
	        ソフトイメージハンドルの取得.
	    */
	    int SoftImageHandleOf( ImageType type );

		//! ロード.
		void Load();

	public:
		//=====================
		//デバッグ用.
		//=====================
	    /**
	    	ファイル名の取得.
	    */
	    static char const* NameOf( ImageType type );
	
	private:
		int ImageHandleOf( char const* name );
		int SoftImageHandleOf( char const* name );
		ImageNameList ImageNameListOf( char const* const name_list[] , int list_size );
	private:
	    ImageNameList const m_image_name_list;
	    ImageMap m_handle_map;
	    ImageMap m_soft_image_handle_list;
	};

} // namespace Game

#endif //Game_SOURCE_PROJECT_SINGLETON_SINGLETONIMAGELOADER

