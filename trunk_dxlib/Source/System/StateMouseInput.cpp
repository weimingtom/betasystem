#include "System/StateBase.hpp"

#include <memory>
#include "DxLibWrapper/DxLibWrapper.hpp"
#include "DxLibWrapper/MouseInput.hpp"
#include "DxLibWrapper/KeyboardInput.hpp"

class StateMouseInput : public StateBase
{
public:
    StateMouseInput();
public:
    void Update();
    void Draw();
private:
    std::auto_ptr< MouseInput > m_mouse;
    std::auto_ptr< KeyboardInput > m_keyboard;
};

StateMouseInput::StateMouseInput()
 : m_mouse( new_MouseInput() )
 , m_keyboard( new_KeyboardInput() )
{
}

void StateMouseInput::Update()
{
    m_mouse->Update();
    m_keyboard->Update();
}

void StateMouseInput::Draw()
{
    DrawFormatString( 10 , 0 , DefaultFontColor() , "TestState." );
    DrawFormatString( 10 , 20 , DefaultFontColor() , "x[%d]y[%d]" , m_mouse->GetX() , m_mouse->GetY() );
    
    DrawFormatString( 10 , 40 , DefaultFontColor() , "right_trig[%d]left_trig[%d]" ,
        m_mouse->IsTrig( MouseInput::Type_Right ) , m_mouse->IsTrig(MouseInput::Type_Left ) );
    DrawFormatString( 10 , 60 , DefaultFontColor() , "right_Hold[%d]left_Hold[%d]" ,
        m_mouse->IsHold( MouseInput::Type_Right ) , m_mouse->IsHold(MouseInput::Type_Left ) );
    
    DrawFormatString( 10 , 80 , DefaultFontColor() , "TrigUp[%d],HoldUp[%d]" ,
        m_keyboard->IsTrig( KeyboardInput::Type_Up ) , m_keyboard->IsHold( KeyboardInput::Type_Up ) );
}

StateBase* new_StateMouseInput()
{
    return new StateMouseInput();
}
