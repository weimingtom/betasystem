#include "StateSushi.hpp"

#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/SingletonStateManager.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/Range.hpp"

namespace Game
{
	StateSushi::StateSushi()
	 : mIndex(0)
	{
	}

	void StateSushi::Update()
	{
		// 上下
	    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){ mIndex--; }
	    else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){ mIndex++; }
        mIndex = Clamp( 0, mIndex, kCharaNum - 1 );

		// エサ食わせ.
	    if( KeyInput()->IsTrig( InputKey::Type_Right ) ){ mCharaList[mIndex].AddFood(); }

		for( int i = 0 ; i < kCharaNum ; i++ ){
		    mCharaList[i].Update();
		}
	}

	void StateSushi::Draw()
	{
	    SetFontSize(12);
	    DrawFormatString( 0, 0, ColorOf(0,255,0) , "寿司ゲー" );

		for( int i = 0 ; i < kCharaNum ; i++ ){
		    DrawFormatString( 0, 20 + i*20 , ColorOf(0,255,0) , "%02d,%03d", mCharaList[i].GetStock(), mCharaList[i].GetFrame() );
		    
		    if( mIndex == i){ DrawFormatString( 50, 20 + i*20 , ColorOf(0,255,0) , "←" ); } 
		}
	}

} // namespace Princess
