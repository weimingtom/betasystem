#include "StateSushi.hpp"

#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/SingletonStateManager.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/Range.hpp"

namespace Game
{
	StateSushi::StateSushi()
	{
	}

	void StateSushi::Update()
	{
	    //if( KeyInput()->IsTrig( InputKey::Type_Up ) ){ mIndex--; }
	}

	void StateSushi::Draw()
	{
	    SetFontSize(12);
	    DrawFormatString( 0, 0, ColorOf(0,255,0) , "寿司ゲー." );
	}

} // namespace Princess
