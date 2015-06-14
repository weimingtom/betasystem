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
	 , mScore(0)
	{
		Character chara;
		mCharaList.push_back( chara );
		mCharaList.push_back( chara );
		mCharaList.push_back( chara );
	}

	void StateSushi::Update()
	{
		// 増える
//		if( mScore >= 1000 && mCharaList.size() == 1 ){
//			Character chara;
//			mCharaList.push_back( chara );
//		}
	
		// 上下
	    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){ mIndex--; }
	    else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){ mIndex++; }
        mIndex = Clamp( 0, mIndex, mCharaList.size() - 1 );

		// 寿司増やし
		if( KeyInput()->IsTrig( InputKey::Type_Right ) ){
			switch_flag = true;
		}
		else if( KeyInput()->IsTrig( InputKey::Type_Left ) ){
			if( switch_flag ){
				switch_flag = false;
				mFoodStock.push_back( (FoodType)GetRand(FoodType_Num) );
			}
		}
		
		// エサ食わせ.
		if( mFoodStock.size() ){
			if( KeyInput()->IsTrig( InputKey::Type_Enter ) ){
				mCharaList.at(mIndex).AddFood( mFoodStock.at(0) );
				mFoodStock.erase( mFoodStock.begin() );
			}
		}

		for( int i = 0 ; i < mCharaList.size() ; i++ ){
		    if( mCharaList.at(i).Update() ){
		    	mScore += 100;
		    }
		}
	}
	
	int StateSushi::GetColor( FoodType food_type )
	{
		switch(food_type){
		case FoodType_Red:		return ColorOf(255,110,110);
		case FoodType_Green:	return ColorOf(110,255,110);
		case FoodType_Blue:
		default:				return ColorOf(110,110,255);
		}
	}

	void StateSushi::Draw()
	{
	    SetFontSize(12);
	    DrawFormatString( 0, 0, ColorOf(0,255,0) , "寿司ゲー:Score[%d]", mScore );
	    
	    for( unsigned int i = 0 ; i < mFoodStock.size(); i++ ){
			DrawFormatString( i * 20 , 50, GetColor( mFoodStock.at(i) ) , "○");
	    }

		for( int i = 0 ; i < mCharaList.size() ; i++ )
		{
		    DrawFormatString( 0, 100 + i*20 , ColorOf(0,255,0) , "%03d", mCharaList.at(i).GetFrame() );

			for( unsigned int j = 0; j<mCharaList.at(i).GetFoodList().size() ; j++ ){
				DrawFormatString( 150+j*20, 100 + i*20 , GetColor( mCharaList.at(i).GetFoodList().at(j).food_type ) , "●" );
			}
		    
		    if( mIndex == i){ DrawFormatString( 50, 100 + i*20 , ColorOf(0,255,0) , "→" ); } 
		}
	}

} // namespace Princess
