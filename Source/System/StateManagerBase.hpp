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
        �J�ڐ؂�ւ�.
    */
    void ChangeState( int state_index )
    {
        m_next_state.reset( new_State( state_index ) );
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
    
protected:
    /**
        �n���ꂽ�C���f�b�N�X�ɑΉ������X�e�[�g�𐶐�����֐�.
        �p�������N���X�́A���̒��g����������K�v������.
    */
    virtual StateBase* new_State( int select_index ) = 0;
    
private:
    std::auto_ptr< StateBase > m_current_state;
    std::auto_ptr< StateBase > m_next_state;
};

#endif

