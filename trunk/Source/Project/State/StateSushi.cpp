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
	}

	void StateSushi::Update()
	{
		// 増える
		if( mScore >= 1000 && mCharaList.size() <= 2 ){
			Character chara;
			mCharaList.push_back( chara );
		}
	
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
				mFoodStock.push_back( static_cast<FoodType>( GetRand( FoodType_Num - 2 ) )  );
				SingletonSoundLoader::Get()->Play( NameOf(SoundType_Landing) );
			}
		}
		
		// エサ食わせ.
		if( mFoodStock.size() ){
			if( KeyInput()->IsTrig( InputKey::Type_Enter ) ){
				SingletonSoundLoader::Get()->Play( NameOf(SoundType_Jump) );
				
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
		case FoodType_Blue:		return ColorOf(110,110,255);
		case FoodType_Normal:	return ColorOf(255,255,255);
		default:				return ColorOf(255,255,255);
		}
	}

	void StateSushi::Draw()
	{
	    SetFontSize(12);
	    DrawFormatString( 0, 0, ColorOf(0,255,0) , "左右を交互に押すと、エサが増えます。Score[%d]", mScore );
	    
	    // ストック.
	    for( unsigned int i = 0 ; i < mFoodStock.size(); i++ ){
			DrawFormatString( i * 20 , 50, GetColor( mFoodStock.at(i) ) , "○", mFoodStock.at(i) );
	    }

		for( int i = 0 ; i < mCharaList.size() ; i++ )
		{
		    DrawFormatString( 0, 100 + i*20, GetColor( mCharaList.at(i).GetColor() ), "(´・ω・)"  );

			// 食ってる途中
			int const kBaseX = 400;
		    DrawFillBox( kBaseX, 100 + i*20, kBaseX + mCharaList.at(i).GetFrame() / 4, 100 + i*20 + 10,  GetColor( mCharaList.at(i).GetColor() )  );

			for( unsigned int j = 0; j<mCharaList.at(i).GetFoodList().size() ; j++ ){
				DrawFormatString( 100+j*20, 100 + i*20 , GetColor( mCharaList.at(i).GetFoodList().at(j).food_type ) , "○" );
			}
		    
		    if( mIndex == i){ DrawFormatString( 80, 100 + i*20 , ColorOf(255,255,255) , "→" ); } 
		}
	}

} // namespace Princess
