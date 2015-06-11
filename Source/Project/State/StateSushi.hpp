#ifndef PRINCESS_SOURCE_PROJECT_STATE_STATESUSHI
#define PRINCESS_SOURCE_PROJECT_STATE_STATESUSHI

#include <vector>
#include "System/StateBase.hpp"
#include "Project/Singleton/SingletonStateManager.hpp"

namespace Game
{
	class StateSushi : public StateBase
	{
	public:
	    StateSushi();
	    ~StateSushi(){}
	public:
	    void Update();
	    void Draw();

	private:
		// 食べ物の種類.
		enum FoodType
		{
			FoodType_None,
			FoodType_Normal,
		};
	
		// キャラ
		struct Character
		{
			Character(){}

			std::vector<int> food_list;	//!< 食べる物リスト
			
			void AddFood()
			{
				if( food_list.size() < 5 ){
					food_list.push_back(250);
				}
			}
			
			void Update()
			{
				if( food_list.size() )
				{
					food_list.at(0)--;
					if( food_list.at(0) <= 0 )
					{
						food_list.erase( food_list.begin() );
					}
				}
			}
			
			int GetFrame()
			{
				if( food_list.size() ){
					return food_list.at(0);
				}
				return 0;
			}
			
			int GetStock()
			{
				return food_list.size();
			}
		};

	private:
		int mIndex;
		static int const kCharaNum = 5;
		Character mCharaList[kCharaNum];
	};

} // namespace Princess

#endif // PRINCESS_SOURCE_PROJECT_STATE_STATESUSHI

