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

void DrawGraphInCamera( int x, int y , PrincessImageLoader::ImageType handle, int touka = TRUE, int hanten = FALSE)
{
	if( hanten == FALSE ){
	    DrawTurnGraph( 
	    	static_cast<int>( x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( y + gCamera2D().GetDrawOffset().y ),
			PrincessImageLoader::ImageHandleOf( handle ),
			touka
		);
	}else{
	    DrawGraph( 
	    	static_cast<int>( x + gCamera2D().GetDrawOffset().x ),
	    	static_cast<int>( y + gCamera2D().GetDrawOffset().y ),
			PrincessImageLoader::ImageHandleOf( handle ),
			touka
		);
	}
}




