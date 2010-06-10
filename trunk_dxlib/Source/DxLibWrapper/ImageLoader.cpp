#include "DxLibWrapper/ImageLoader.hpp"

#include <string>
#include <vector>
#include "DxLibWrapper/DxLibWrapper.hpp"

typedef std::vector<std::string> ImageNameList;
typedef std::map< std::string , int > ImageMap;

class ImageLoader::Impl: public ImageLoader
{
public:
    Impl( char const* const name_list[] );
    ~Impl();
    
public:
    void Load();
    int ImageHandleOf( char const* name );
    
private:
    ImageNameList ImageNameListOf( char const* const name_list[] );
    
private:
    ImageNameList const m_image_name_list;
    ImageMap m_handle_map;
};

ImageLoader::Impl::Impl( char const* const name_list[] )
 : m_image_name_list( ImageNameListOf( name_list ) )
{
}

ImageLoader::Impl::~Impl()
{
}

void ImageLoader::Impl::Load()
{
    for( ImageNameList::size_type i = 0 ; i < m_image_name_list.size() ; i ++ )
    {
        int const handle = LoadGraph( m_image_name_list[i].c_str() );
        assert( handle != -1 && "LoadGraph() Failed." );
        
        m_handle_map.insert(
            ImageMap::value_type( m_image_name_list[i] , handle ) );
    }
}

int ImageLoader::Impl::ImageHandleOf( char const* name )
{
    std::string const name_str( name );
    ImageMap::iterator it = m_handle_map.find( name_str );
    assert( it != end && "m_handle_map.find() failed." );
    return (*it).second();
}

ImageNameList ImageLoader::Impl::ImageNameListOf( char const* const name_list[] )
{
    ImageNameList result;
    for( int i = 0 ; i < ArraySize( name_list ) ; i ++ )
    {
        result.push_back( name_list[i] );
    }
    return result;
}

