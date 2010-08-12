#ifndef include_ac9717c6_ce6b_4b63_82d7_a4e03023f3d8
#define include_ac9717c6_ce6b_4b63_82d7_a4e03023f3d8

class Character;
#include "Project/BackgroundFactory.hpp"

class MapBase
{
public:
    virtual ~MapBase(){}
    
public:
    virtual bool HasNextMonster() = 0;
    /**
        次のモンスターを取得.
    */
    virtual Character NextMonster() = 0;
};

MapBase* new_Map( BackgroundType back_ground_type );

#endif

