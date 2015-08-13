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
		�摜�̎��.
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
		    �C���X�^���X�̎擾.
		*/
		static ImageLoader* GetInstance();

		/**
			������.
		*/
		static void Initialize();

	    /**
	        �J������.
	    */
	    static void Finalize();
	private:
		ImageLoader();

	public:
		~ImageLoader();

	public:
	    /**
	        �C���[�W�n���h���擾.
	    */
	    int ImageHandleOf( ImageType type );

		
	    /**
	        �\�t�g�C���[�W�n���h���̎擾.
	    */
	    int SoftImageHandleOf( ImageType type );

		//! ���[�h.
		void Load();

	public:
		//=====================
		//�f�o�b�O�p.
		//=====================
	    /**
	    	�t�@�C�����̎擾.
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

