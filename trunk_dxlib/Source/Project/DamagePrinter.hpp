#ifndef include_2c3a0e8f_7d4e_46de_ae84_9eb6e06171c9
#define include_2c3a0e8f_7d4e_46de_ae84_9eb6e06171c9

#include "System/Vector2.hpp"

class DamagePrinter
{
public:
    friend DamagePrinter* new_DamagePrinter();
    virtual ~DamagePrinter(){}

public:
    virtual void Begin( Vector2 pos , int damage ) = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    
private:
    class Impl;
};

DamagePrinter* new_DamagePrinter();

#endif

