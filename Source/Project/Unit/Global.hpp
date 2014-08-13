#ifndef IncludeGuard_Global_hpp_
#define IncludeGuard_Global_hpp_

#include "System/Vector2.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

bool IsVisibleCollision();
void SetVisibleCollision( bool is_visible );

void DrawGraphInCamera( Vector2 pos, Vector2 size, int anim_index, PrincessImageLoader::ImageType handle, int touka = TRUE, int hanten = FALSE);


enum{
	kMapChipMax = 32,
};

//! マップチップの取得.
int GetMapChip( int x, int y );

//! マップチップ設定.
void  SetMapChip( int x, int y, int chip_type );

#endif // IncludeGuard_Global_hpp_
