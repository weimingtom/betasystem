#include "DxLibWrapper/SoundLoader.hpp"

#include <map>
#include <assert.h>
#include <DxLib.h>
#include "DxLibWrapper/ReturnVariable.hpp"

typedef std::map< std::string , int > HandleMap;

class SoundLoader::Impl: public SoundLoader
{
public:
    Impl( StringList file_name_list );
    ~Impl();
    
public:
    void Load();
    void Play( std::string file_name , bool is_bgm );
    
private:
    StringList const m_file_name_list;
    HandleMap m_handle_map;
};

SoundLoader::Impl::Impl( StringList file_name_list )
 : m_file_name_list( file_name_list )
{
}

SoundLoader::Impl::~Impl()
{
    // 確保したハンドルを全て解放する.
    HandleMap::iterator it = m_handle_map.begin();
    HandleMap::iterator const end_it = m_handle_map.end();
    
    while( it != m_handle_map.end() )
    {
        if( DeleteSoundMem( (*it).second ) == FunctionFailure )
        {
            assert( false );
            exit( DxLib_Failure );
        }
        it++;
    }
}

void SoundLoader::Impl::Load()
{
    for( StringList::size_type i = 0 ; i < m_file_name_list.size() ; i ++ )
    {
        int const handle = LoadSoundMem( m_file_name_list[i].c_str() );
        assert( handle != -1 && "LoadSoundMem() Failed." );
        
        m_handle_map.insert(
            HandleMap::value_type( m_file_name_list[i] , handle ) );
    }
}

void SoundLoader::Impl::Play( std::string file_name , bool is_bgm )
{
    HandleMap::iterator it = m_handle_map.find( file_name );
    assert( it != m_handle_map.end() && "m_handle_map.find() failed." );

    if( is_bgm )
    {
        PlaySoundMem( (*it).second , DX_PLAYTYPE_LOOP , TRUE );
    }else{
        PlaySoundMem( (*it).second , DX_PLAYTYPE_BACK , TRUE );
    }
    //ボリューム変更.
	int const result = ChangeVolumeSoundMem(50,(*it).second);
}

SoundLoader* new_SoundLoader( StringList file_name_list )
{
    return new SoundLoader::Impl( file_name_list );
}

