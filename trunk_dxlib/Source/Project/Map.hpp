#ifndef include_ac9717c6_ce6b_4b63_82d7_a4e03023f3d8
#define include_ac9717c6_ce6b_4b63_82d7_a4e03023f3d8

class CharacterStatus;
#include "Project/BackgroundFactory.hpp"

class MapBase
{
public:
    virtual ~MapBase(){}
    
public:
    virtual bool HasNextMonster() = 0;
    /**
        Ÿ‚Ìƒ‚ƒ“ƒXƒ^[‚ğæ“¾.
    */
    virtual CharacterStatus NextMonster() = 0;
};

MapBase* new_Map( BackgroundType back_ground_type );

#endif

