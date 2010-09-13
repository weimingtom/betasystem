#include "Project/Map.hpp"

#include <assert.h>
#include <vector>
#include "Project/CharacterStatusFactory.hpp"
#include "System/ArraySize.hpp"
#include "DxLibWrapper/DxLibWrapper.hpp"

typedef std::vector<CharacterStatus> CharacterStatusList;

class MapGreenForest : public MapBase
{
public:
    MapGreenForest();
public:
    bool HasNextMonster();
    CharacterStatus NextMonster();
private:
    CharacterStatusList::size_type m_monster_index;
    CharacterStatusList m_monster_list;
};

MapGreenForest::MapGreenForest()
 : m_monster_index(0)
{
    CharaType monster_list[] =
    {
        CharaType_GreenSlime,
        CharaType_GreenSlime,
        CharaType_GreenSlime,
        CharaType_GreenSlime,
        CharaType_BigGreenSlime,
    };
    for( int i = 0 ; i < ARRAY_SIZE( monster_list ) ; i++ )
    {
        m_monster_list.push_back( CharacterStatusOf( monster_list[i] ) );
    }
}

bool MapGreenForest::HasNextMonster()
{
    return( m_monster_index < m_monster_list.size() );
}

CharacterStatus MapGreenForest::NextMonster()
{
    if( !HasNextMonster() ){ assert( false); exit(ApplicationFailure); }
    CharacterStatus const result = m_monster_list[ m_monster_index ];
    m_monster_index++;
    return result;
}


class MapRedForest : public MapBase
{
public:
    MapRedForest();
public:
    bool HasNextMonster();
    CharacterStatus NextMonster();
private:
    CharacterStatusList::size_type m_monster_index;
    CharacterStatusList m_monster_list;
};

MapRedForest::MapRedForest()
 : m_monster_index(0)
{
    CharaType monster_list[] =
    {
        CharaType_GreenSlime,
        CharaType_GreenSlime,
        CharaType_BigGreenSlime,
        CharaType_BigGreenSlime,
        CharaType_BigGreenSlime,
        CharaType_BigGreenSlime,
        CharaType_BigGreenSlime,
        CharaType_BigGreenSlime,
    };
    for( int i = 0 ; i < ARRAY_SIZE( monster_list ) ; i++ )
    {
        m_monster_list.push_back( CharacterStatusOf( monster_list[i] ) );
    }
}

bool MapRedForest::HasNextMonster()
{
    return( m_monster_index < m_monster_list.size() );
}

CharacterStatus MapRedForest::NextMonster()
{
    if( !HasNextMonster() ){ assert( false); exit(ApplicationFailure); }
    CharacterStatus const result = m_monster_list[ m_monster_index ];
    m_monster_index++;
    return result;
}


MapBase* new_Map( BackgroundType back_ground_type )
{
    switch( back_ground_type )
    {
    case BackgroundType_Forest:
        return new MapGreenForest();
    case BackgroundType_RedForest:
        return new MapRedForest();
    }
    assert( false );
    exit( ApplicationFailure );
}

