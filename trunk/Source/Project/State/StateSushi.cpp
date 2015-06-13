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

		// 寿司増やし
		if( KeyInput()->IsTrig( InputKey::Type_Right ) ){
			switch_flag = true;
		}
		else if( KeyInput()->IsTrig( InputKey::Type_Left ) ){
			if(switch_flag){
				switch_flag = false;
				mFoodStock.push_back( (FoodType)GetRand(FoodType_Num) );
			}
		}
		
		// エサ食わせ.
		if( mFoodStock.size() ){
			if( KeyInput()->IsTrig( InputKey::Type_Enter ) ){
				mCharaList[mIndex].AddFood( mFoodStock.at(0) );
				mFoodStock.erase( mFoodStock.begin() );
			}
		}

		for( int i = 0 ; i < kCharaNum ; i++ ){
		    mCharaList[i].Update();
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
	    DrawFormatString( 0, 0, ColorOf(0,255,0) , "寿司ゲー");
	    
	    for( unsigned int i = 0 ; i < mFoodStock.size(); i++ ){
			DrawFormatString( i * 20 , 50, GetColor( mFoodStock.at(i) ) , "○");
	    }

		for( int i = 0 ; i < kCharaNum ; i++ )
		{
		    DrawFormatString( 0, 100 + i*20 , ColorOf(0,255,0) , "%03d", mCharaList[i].GetFrame() );

			for( unsigned int j = 0; j<mCharaList[i].GetFoodList().size() ; j++ ){
				DrawFormatString( 150+j*20, 100 + i*20 , GetColor( mCharaList[i].GetFoodList().at(j).food_type ) , "●" );
			}
		    
		    if( mIndex == i){ DrawFormatString( 50, 100 + i*20 , ColorOf(0,255,0) , "→" ); } 
		}
	}

} // namespace Princess
