#ifndef state_AvaterTest_hpp
#define state_AvaterTest_hpp

class StateManagerBase;
#include "System/StateBase.hpp"
#include "Project/AvaterParam.hpp"

//アバター要素
enum AvaterType{
	AvaterType_Option,
	AvaterType_Cloth,
	AvaterType_Hair,
	AvaterType_HairColor,
	AvaterType_Face,
	
	AvaterType_Num
};

class StateAvaterTest : public StateBase
{
public:
    StateAvaterTest( StateManagerBase* manager );
    ~StateAvaterTest(){}
public:
	void Update();
	void Draw() const;
private:
    StateManagerBase* m_manager;
	int m_select_y;
	AvaterParam m_avater;
	int m_select_x[AvaterType_Num];
};

#endif
