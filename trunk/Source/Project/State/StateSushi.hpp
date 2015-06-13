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
		FoodType_Num,
	};

	// キャラ.
	class Character
	{
	public:
		Character(){}
		~Character(){}

	public:
		struct Food{
			FoodType food_type;
			int frame_count;
		};
	
		std::vector<Food> food_list;	//!< 食べる物リスト
		
		void AddFood( FoodType food_type )
		{
			Food food;
			food.food_type = food_type;
			food.frame_count = 400;
		
			if( food_list.size() < 5 ){
				food_list.push_back(food);
			}
		}
		
		void Update()
		{
			if( food_list.size() )
			{
				food_list.at(0).frame_count--;
				if( food_list.at(0).frame_count <= 0 )
				{
					food_list.erase( food_list.begin() );
				}
			}
		}
		
		int GetFrame()
		{
			if( food_list.size() ){
				return food_list.at(0).frame_count;
			}
			return 0;
		}
		
		std::vector<Food> GetFoodList(){ return food_list; }
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
		static int const kCharaNum = 3;
		Character mCharaList[kCharaNum];
		std::vector<FoodType> mFoodStock;
		bool switch_flag;
	};

} // namespace Princess

#endif // PRINCESS_SOURCE_PROJECT_STATE_STATESUSHI

