#ifndef include_d23c908b_64dd_47e6_b17e_168a6dbccd2c
#define include_d23c908b_64dd_47e6_b17e_168a6dbccd2c

#include <memory>
#include "System/StateBase.hpp"

/**
    ‘JˆÚŠÇ—ƒNƒ‰ƒX.
*/
class StateManagerBase
{
public:
    StateManagerBase()
     : m_current_state(0)
    {
    }
    virtual ~StateManagerBase(){}
    
public:
    void ChangeState( int state_index )
    {
        m_current_state.reset( new_State( state_index ) );
    }
    void Update()
    {
        m_current_state->Update();
    }
    void Draw()
    {
        m_current_state->Draw();
    }
    
protected:
    //‚±‚ê‚¾‚¯‚Í©ì‚µ‚Ä‚à‚ç‚¤.
    virtual StateBase* new_State( int select_index ) = 0;
    
private:
    std::auto_ptr< StateBase > m_current_state;
};

#endif

