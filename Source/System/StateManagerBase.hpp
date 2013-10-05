#ifndef include_d23c908b_64dd_47e6_b17e_168a6dbccd2c
#define include_d23c908b_64dd_47e6_b17e_168a6dbccd2c

#include <memory>
#include "System/StateBase.hpp"

/**
     State�Ǘ��N���X�̊�{�ƂȂ�N���X.
     State�̑J�ڂ��Ǘ��������ꍇ�̓R�����p�����Ďg��.
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
        �J�ڐ؂�ւ�.�C���X�^���X�̊Ǘ��͂��̃N���X�����.
        @param next_state �؂�ւ���State�̃|�C���^.
    */
    void ChangeState( StateBase* next_state )
    {
        m_next_state.reset( next_state );
    }
    /**
        �X�V.
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
        �`��.
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

