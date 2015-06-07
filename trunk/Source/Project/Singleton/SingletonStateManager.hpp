#ifndef include_4043f656_29d2_4fa5_b7b8_641d2d447994
#define include_4043f656_29d2_4fa5_b7b8_641d2d447994

#include <string>
#include "../../System/StateManagerBase.hpp"

namespace Princess
{

	/**
	    �v���W�F�N�g�̈�ԏ�Ɉʒu����StateManager.
	*/
	class StateManager : public StateManagerBase
	{
	public:
	    //! �X�e�[�g.
	    enum State{
	        State_DebugTop,     //!< �f�o�b�O�g�b�v.
	        State_Action,       //!< �A�N�V�����e�X�g.
	        State_LuaTest,      //!< lua�e�X�g.
	        State_DrawTexture,  //!< �摜�`��e�X�g.
	        State_CreateChara,  //!< �L��������.
	        State_Num,
	    };

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

	private:
	    //! �R���X�g���N�^.
	    StateManager();
	};

} // end of namespace Princess

#endif

