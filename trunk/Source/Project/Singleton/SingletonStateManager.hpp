#ifndef PRINCESS_SOURCE_PROJECT_SINGLETON_SINGLETONSTATEMANAGER
#define PRINCESS_SOURCE_PROJECT_SINGLETON_SINGLETONSTATEMANAGER

#include <string>
#include <memory>
#include "System/Statebase.hpp"

namespace Princess
{
    //! �X�e�[�g.
    enum State{
        State_DebugTop,     //!< �f�o�b�O�g�b�v.
        State_Action,       //!< �A�N�V�����e�X�g.
        State_LuaTest,      //!< lua�e�X�g.
        State_DrawTexture,  //!< �摜�`��e�X�g.
        State_CreateChara,  //!< �L��������.
        State_Num,
    };

	/**
	    �v���W�F�N�g�̈�ԏ�Ɉʒu����StateManager.
	*/
	class StateManager
	{
	public:
	    //! �f�X�g���N�^.
	    ~StateManager();

	public:
	    //! �X�e�[�g�}�l�[�W���̃|�C���^�擾.
	    static StateManager* GetInstance();

	    //! �C���X�^���X�̍폜.
	    static void DeleteInstance();

	    //! �X�e�[�g�C���X�^���X�̐���.
	    //! @param state �����������X�e�[�g�̎��.
	    static StateBase* new_State(State state);

	    //! ���O�̎擾.
	    static std::string NameOf(State state);

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
	    //! �R���X�g���N�^.
	    StateManager();
	    
	private:
	    std::auto_ptr< StateBase > m_current_state;
	    std::auto_ptr< StateBase > m_next_state;
	};

} // end of namespace Princess

#endif // PRINCESS_SOURCE_PROJECT_SINGLETON_SINGLETONSTATEMANAGER

