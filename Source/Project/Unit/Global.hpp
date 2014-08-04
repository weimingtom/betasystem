#ifndef IncludeGuard_Global_hpp_
#define IncludeGuard_Global_hpp_

#include "Project/Singleton/SingletonImageLoader.hpp"

bool IsVisibleCollision();
void SetVisibleCollision( bool is_visible );

void DrawGraphInCamera( Vector2 pos, Vector2 size, int anim_index, PrincessImageLoader::ImageType handle, int touka = TRUE, int hanten = FALSE);


#endif // IncludeGuard_Global_hpp_
