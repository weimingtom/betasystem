#include "Project/BackgroundFactory.hpp"

namespace {

BackgroundType s_back_ground_type = BackgroundType_Forest;

} // namespace unnamed


void SetBackground( BackgroundType type )
{
    s_back_ground_type = type;
}

BackgroundType GetBackground()
{
    return s_back_ground_type;
}

