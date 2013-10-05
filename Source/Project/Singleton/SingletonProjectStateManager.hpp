#ifndef include_4043f656_29d2_4fa5_b7b8_641d2d447994
#define include_4043f656_29d2_4fa5_b7b8_641d2d447994

#include "../../System/StateManagerBase.hpp"

/**
    �v���W�F�N�g�̈�ԏ�Ɉʒu����StateManager.
*/
class SingletonProjectStateManager : public StateManagerBase
{
public:
    //! �X�e�[�g.
    enum State{
        State_DebugTop,
        State_Title,
        State_Num,
    };
public:
    //! �f�X�g���N�^.
    ~SingletonProjectStateManager();
public:
    //! �X�e�[�g�}�l�[�W���̃|�C���^�擾.
    static SingletonProjectStateManager* GetInstance();
    //! �X�e�[�g�C���X�^���X�̐���.
    //! @param state �����������X�e�[�g�̎��.
    static StateBase* new_State(State state);
private:
    //! �R���X�g���N�^.
    SingletonProjectStateManager();
};

#endif

