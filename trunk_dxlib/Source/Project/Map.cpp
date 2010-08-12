#include "Project/Map.hpp"

#include <assert.h>
#include <vector>
#include "Project/CharacterFactory.hpp"
#include "System/ArraySize.hpp"
#include "DxLibWrapper/DxLibWrapper.hpp"

typedef std::vector<Character> CharacterList;

class MapGreenForest : public MapBase
{
public:
    MapGreenForest();
public:
    bool HasNextMonster();
    Character NextMonster();
private:
    CharacterList::size_type m_monster_index;
    CharacterList m_monster_list;
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
        m_monster_list.push_back( CharacterOf( monster_list[i] ) );
    }
}

bool MapGreenForest::HasNextMonster()
{
    return( m_monster_index < m_monster_list.size() );
}

Character MapGreenForest::NextMonster()
{
    if( !HasNextMonster() ){ assert( false); exit(ApplicationFailure); }
    Character const result = m_monster_list[ m_monster_index ];
    m_monster_index++;
    return result;
}

MapBase* new_Map( BackgroundType back_ground_type )
{
    return new MapGreenForest();
}

