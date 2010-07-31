#include "Project/SaveData.hpp"

#include <memory>
#include "Project/CharacterFactory.hpp"

namespace{

static std::auto_ptr< SaveData > g_save_data;

} // namespace unnamed

SaveData::SaveData()
 : m_player_status( CharacterOf( CharaType_Player ) )
{
}

SaveData& SaveData::GetInstance()
{
    if( !g_save_data.get() )
    {
        g_save_data.reset( new SaveData() );
    }
    return *g_save_data;
}

