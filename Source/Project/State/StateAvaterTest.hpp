#ifndef state_AvaterTest_hpp
#define state_AvaterTest_hpp

class StateManagerBase;
#include "System/StateBase.hpp"
#include "Project/Avater/AvaterParam.hpp"

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
    StateAvaterTest();
    ~StateAvaterTest(){}
public:
	void Update();
	void Draw() const;
private:
	int m_select_y;
	AvaterParam m_avater;
	int m_select_x[AvaterType_Num];
};

#endif
