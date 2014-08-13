#include "Global.hpp"
#include "Project/Unit/UnitPlayer.hpp"
#include "Project/Camera2D/Camera2D.hpp"

static bool gIsVisibleCollision = false;

bool IsVisibleCollision()
{
	return gIsVisibleCollision;
}

void SetVisibleCollision( bool is_visible )
{
	gIsVisibleCollision = is_visible;
}

void DrawGraphInCamera( Vector2 pos, Vector2 size, int anim_index,PrincessImageLoader::ImageType handle, int touka , int hanten )
{
	DrawRectGraph(
    	static_cast<int>( pos.x + gCamera2D().GetDrawOffset().x ),
    	static_cast<int>( pos.y + gCamera2D().GetDrawOffset().y ),
		anim_index*size.x,0,
		size.x,size.y,
		PrincessImageLoader::ImageHandleOf( handle ),
		touka,
		!hanten
	);
}

static int sMapChip[kMapChipMax][kMapChipMax];

int GetMapChip( int x, int y )
{
	return sMapChip[y][x];
}

void SetMapChip( int x, int y, int chip_type )
{
	sMapChip[y][x] = chip_type;
}


