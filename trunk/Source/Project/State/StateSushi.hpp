#ifndef PRINCESS_SOURCE_PROJECT_STATE_STATESUSHI
#define PRINCESS_SOURCE_PROJECT_STATE_STATESUSHI

#include <vector>
#include "System/StateBase.hpp"
#include "Project/Singleton/SingletonStateManager.hpp"

namespace Game
{
	// 食べ物の種類.
	enum FoodType
	{
		FoodType_Red,
		FoodType_Green,
		FoodType_Blue,
		FoodType_Normal,
		FoodType_Num,
	};

	// キャラ.
	class Character
	{
	public:
		Character()
		 : mEatNum(0)
		 , mColor(FoodType_Normal)
		{}
		~Character()
		{}

	public:
		struct Food{
			FoodType food_type;
			int frame_count;
		};
	
		void AddFood( FoodType food_type )
		{
			Food food;
			food.food_type = food_type;
			food.frame_count = 400;
		
			if( food_list.size() < 5 ){
				food_list.push_back(food);
			}
		}
		
		bool Update()
		{
			if( food_list.size() )
			{
				if( food_list.at(0).food_type == mColor ){
					food_list.at(0).frame_count -= 2;
				}else{
					food_list.at(0).frame_count -= 1;
				}

				if( food_list.at(0).frame_count <= 0 )
				{
					// 食い終わった
					mColor = food_list.at(0).food_type;
					food_list.erase( food_list.begin() );
					mEatNum++;
					return true;
				}
			}
			return false;
		}
		
		int GetFrame()
		{
			if( food_list.size() ){
				return food_list.at(0).frame_count;
			}
			return 0;
		}
		
		std::vector<Food> GetFoodList(){ return food_list; }

		FoodType GetColor() const{ return mColor; }

	private:
		std::vector<Food> food_list;	//!< 食べる物リスト
		int mEatNum;
		FoodType mColor;
	};



	class StateSushi : public StateBase
	{
	public:
	    StateSushi();
	    ~StateSushi(){}
	public:
	    void Update();
	    void Draw();
	
	private:
		int GetColor(FoodType);

	private:
		int mIndex;
		std::vector<Character> mCharaList;
		std::vector<FoodType> mFoodStock;
		bool switch_flag;
		int mScore;
	};

} // namespace Princess

#endif // PRINCESS_SOURCE_PROJECT_STATE_STATESUSHI

