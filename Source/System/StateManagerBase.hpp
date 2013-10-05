#ifndef include_d23c908b_64dd_47e6_b17e_168a6dbccd2c
#define include_d23c908b_64dd_47e6_b17e_168a6dbccd2c

#include <memory>
#include "System/StateBase.hpp"

/**
     State管理クラスの基本となるクラス.
     Stateの遷移を管理したい場合はコレを継承して使う.
*/
class StateManagerBase
{
public:
    StateManagerBase()
     : m_current_state(0)
     , m_next_state(0)
    {
    }
    virtual ~StateManagerBase(){}
    
public:
    /**
        遷移切り替え.インスタンスの管理はこのクラスがやる.
        @param next_state 切り替えるStateのポインタ.
    */
    void ChangeState( StateBase* next_state )
    {
        m_next_state.reset( next_state );
    }
    /**
        更新.
    */
    void Update()
    {
        if( m_next_state.get() )
        {
            m_current_state.reset( m_next_state.release() );
        }
        m_current_state->Update();
    }
    /**
        描画.
    */
    void Draw()
    {
        m_current_state->Draw();
    }
    
private:
    std::auto_ptr< StateBase > m_current_state;
    std::auto_ptr< StateBase > m_next_state;
};

#endif

