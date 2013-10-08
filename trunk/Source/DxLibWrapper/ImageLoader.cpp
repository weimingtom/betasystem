#include "DxLibWrapper/ImageLoader.hpp"

#include <string>
#include <map>
#include <assert.h>
#include <vector>
#include <DxLib.h>
#include "DxLibWrapper/ReturnVariable.hpp"

typedef std::vector<std::string> ImageNameList;
typedef std::map< std::string , int > ImageMap;

class ImageLoader::Impl: public ImageLoader
{
public:
    Impl( char const* const name_list[] , int list_size );
    ~Impl();
    
public:
    void Load();
    int ImageHandleOf( char const* name );
    int SoftImageHandleOf( char const* name );
private:
    ImageNameList ImageNameListOf( char const* const name_list[] , int list_size );
    
private:
    ImageNameList const m_image_name_list;
    // ファイル名から取得できるように連想配列として登録する.
    ImageMap m_handle_map;
    ImageMap m_soft_image_handle_list;
};

ImageLoader::Impl::Impl( char const* const name_list[] , int list_size )
 : m_image_name_list( ImageNameListOf( name_list , list_size ) )
{
    SetTransColor(0,255,0);
}

ImageLoader::Impl::~Impl()
{
    // イメージハンドルの削除.
	{
		ImageMap::iterator it = m_handle_map.begin();
		while( it != m_handle_map.end() )
		{
			if( DeleteGraph( (*it).second ) == FunctionFailure ){
				assert( false );
				exit( ApplicationFailure );
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
				exit( ApplicationFailure );
			}
			it++;
		}
	}
}

void ImageLoader::Impl::Load()
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

int ImageLoader::Impl::ImageHandleOf( char const* name )
{
    std::string const name_str( name );
    ImageMap::iterator it = m_handle_map.find( name_str );
    assert( it != m_handle_map.end() && "m_handle_map.find() failed." );
    return (*it).second;
}

int ImageLoader::Impl::SoftImageHandleOf( char const* name )
{
    std::string const name_str( name );
    ImageMap::iterator it = m_soft_image_handle_list.find( name_str );
    assert( it != m_soft_image_handle_list.end() && "m_handle_map.find() failed." );
    return (*it).second;
}

ImageNameList ImageLoader::Impl::ImageNameListOf( char const* const name_list[] , int list_size )
{
    ImageNameList result;
    for( int i = 0 ; i < list_size ; i ++ )
    {
        result.push_back( name_list[i] );
    }
    return result;
}

ImageLoader* new_ImageLoader( char const* const name_list[] , int list_size )
{
    return new ImageLoader::Impl( name_list , list_size );
}

