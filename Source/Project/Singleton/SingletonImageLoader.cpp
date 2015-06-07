#include "SingletonImageLoader.hpp"

#include <assert.h>
#include <memory>
#include <DxLib.h>
#include "DxLibWrapper/ReturnVariable.hpp"

namespace Princess
{
	/**
		使用する画像名.
	*/
	char const* const image_name[ ImageType_Num ] =
	{
	    "Resource/map.png",
	    "Resource/map2.png",
	    "Resource/shadow.png",
	    "Resource/Avater.bmp",
	    "Resource/player.png",
	    "Resource/enemy.png",
	    "Resource/shot.png",
	    "Resource/paricle.png",
	    "Resource/map_object.png",
	    "Resource/item.png",
	};

	//! シングルトンインスタンス.
	std::auto_ptr<ImageLoader> sImageLoader;

	ImageLoader* ImageLoader::GetInstance()
	{
		return sImageLoader.get();
	}

	ImageLoader::ImageLoader()
	 : m_image_name_list( ImageNameListOf( image_name, ImageType_Num ) )
	{
	    SetTransColor(0,255,0);
	}
	
	ImageLoader::~ImageLoader()
	{
	    // イメージハンドルの削除.
		{
			ImageMap::iterator it = m_handle_map.begin();
			while( it != m_handle_map.end() )
			{
				if( DeleteGraph( (*it).second ) == FunctionFailure ){
					assert( false );
					exit( DxLib_Failure );
				}
				it++;
			}
		}
	    // ソフトイメージハンドルの削除.
		{
			ImageMap::iterator it = m_soft_image_handle_list.begin();
			while( it != m_soft_image_handle_list.end() )
			{
				if( DeleteSoftImage( (*it).second ) == FunctionFailure ){
					assert( false );
					exit( DxLib_Failure );
				}
				it++;
			}
		}
	}

	void ImageLoader::Initialize()
	{
		sImageLoader.reset( new ImageLoader() );
		sImageLoader->Load();
	}
	
	void ImageLoader::Finalize()
	{
	    sImageLoader.reset(0);
	}

    int ImageLoader::ImageHandleOf( ImageType type )
    {
        return GetInstance()->ImageHandleOf( NameOf(type) );
    }

    int ImageLoader::SoftImageHandleOf( ImageType type )
    {
        return GetInstance()->SoftImageHandleOf( NameOf(type) );
    }

	int ImageLoader::ImageHandleOf( char const* name )
	{
	    std::string const name_str( name );
	    ImageMap::iterator it = m_handle_map.find( name_str );
	    assert( it != m_handle_map.end() && "m_handle_map.find() failed." );
	    return (*it).second;
	}

	int ImageLoader::SoftImageHandleOf( char const* name )
	{
	    std::string const name_str( name );
	    ImageMap::iterator it = m_soft_image_handle_list.find( name_str );
	    assert( it != m_soft_image_handle_list.end() && "m_handle_map.find() failed." );
	    return (*it).second;
	}

	ImageNameList ImageLoader::ImageNameListOf( char const* const name_list[] , int list_size )
	{
	    ImageNameList result;
	    for( int i = 0 ; i < list_size ; i ++ )
	    {
	        result.push_back( name_list[i] );
	    }
	    return result;
	}

	void ImageLoader::Load()
	{
	    for( ImageNameList::size_type i = 0 ; i < m_image_name_list.size() ; i ++ )
	    {
	        //イメージハンドルの作成.
	        int const handle = LoadGraph( m_image_name_list[i].c_str() );
	        assert( handle != -1 && "LoadGraph() Failed." );
	        m_handle_map.insert(
	            ImageMap::value_type( m_image_name_list[i] , handle ) );
	        //ソフトイメージハンドルの作成.
	        int const soft_image_handle = LoadSoftImage( m_image_name_list[i].c_str() );
	        assert( soft_image_handle != -1 && "LoadGraph() Failed." );
	        m_soft_image_handle_list.insert(
	            ImageMap::value_type( m_image_name_list[i] , soft_image_handle ) );
	    }
	}

    char const* ImageLoader::NameOf( ImageType type )
    {
    	return image_name[type];
    }

} // namespace Princess

