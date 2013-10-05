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
        遷移切り替え.
    */
    void ChangeState( int state_index )
    {
        m_next_state.reset( new_State( state_index ) );
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
    
protected:
    /**
        渡されたインデックスに対応したステートを生成する関数.
        継承したクラスは、この中身を実装する必要がある.
    */
    virtual StateBase* new_State( int select_index ) = 0;
    
private:
    std::auto_ptr< StateBase > m_current_state;
    std::auto_ptr< StateBase > m_next_state;
};

#endif

