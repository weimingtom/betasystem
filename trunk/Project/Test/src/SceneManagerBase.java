import com.nttdocomo.ui.Display;

/**
    �V�[���Ǘ��N���X.
*/
abstract class SceneManagerBase
{
    //! ���݂̃V�[��.
    private SceneBase m_current_scene;
    
    /**
        ���݂� Scene ��Ԃ��֐�.
    */
    public SceneBase CurrentScene()
    {
        return m_current_scene;
    }
    
    /**
        Scene �؂�ւ��֐�.
        @param scene_index Scene �Ǘ��ԍ�.
    */
    public void ChangeScene( int scene_index )
    {
        System.out.println("ChangeScene()");
        
        m_current_scene = new_Scene( scene_index );
        Display.setCurrent( m_current_scene );
        m_current_scene.Init();
    }
    
    /**
        Scene �Ǘ��ԍ����� Scene �𐶐�����֐�.
        @param scene_index Scene �Ǘ��ԍ�.
    */
    abstract SceneBase new_Scene( int scene_index );
};

