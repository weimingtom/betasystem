import java.util.*;

/**
    ���[���h�}�b�v�ŕ\�������e�t�B�[���h��\������N���X.
*/
class Stage
{
    String m_name; //!< �t�B�[���h����.
    Vector m_monster_list; //!< �o�����郂���X�^�[�̃��X�g.
    
    /**
        �R���X�g���N�^.
    */
    Stage(
        String name ,
        Vector monster_list )
    {
        m_name = name;
        m_monster_list = monster_list;
    }
};

