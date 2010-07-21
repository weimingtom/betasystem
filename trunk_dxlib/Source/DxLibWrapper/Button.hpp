#ifndef include_c5b4571e_b687_429b_aa72_b7a2a9dd5334
#define include_c5b4571e_b687_429b_aa72_b7a2a9dd5334

#include "System/Vector2.hpp"
#include "System/ProcessBase.hpp"

class Button
{
public:
    /**
        processのdeleteはこのクラスが行う.
    */
    friend Button* new_Button(
        int image_handle ,
        Vector2 pos ,
        Vector2 size ,
        ProcessBase* process );
    virtual ~Button(){}
    
public:
    virtual void Draw() const = 0;
    virtual bool CheckHit( Vector2 pos ) const = 0;
    virtual void Process() = 0;
    
private:
    class Impl;
};

Button* new_Button(
    int image_handle ,
    Vector2 pos ,
    Vector2 size ,
    ProcessBase* process = 0 );

#endif

