#include "Project/SaveData.hpp"

#include <memory>

namespace{

static std::auto_ptr< SaveData > g_save_data;

} // namespace unnamed

SaveData::SaveData()
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

