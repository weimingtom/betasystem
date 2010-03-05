import com.nttdocomo.ui.Display;

/**
    Scene �̐؂�ւ����Ǘ�����N���X.
*/
class SceneChangeManager
{
    /*
        Scene �Ǘ��ԍ�.
    */
    public static final int Scene_Title = 0; //!< �^�C�g�����.
    public static final int Scene_Battle  = 1; //!< ���C�����.
    
    //! ���݂̃V�[��.
    private SceneBase m_current_scene;
    
    /**
        �R���X�g���N�^.
    */
    SceneChangeManager()
    {
        ChangeScene( Scene_Title );
    }
    
    /**
        ���݂� Scene ��Ԃ��֐�.
    */
    public SceneBase CurrentScene()
    {
        return m_current_scene ;
    }
    
    /**
        Scene �؂�ւ��֐�.
        @param scene_index Scene �Ǘ��ԍ�.
    */
    public void ChangeScene( int scene_index )
    {
        m_current_scene = new_Scene( scene_index );
        Display.setCurrent( m_current_scene );
        m_current_scene.Init();
    }
    
    /**
        Scene �Ǘ��ԍ�����A Scene �𐶐�����֐�.
        @param scene_index Scene �Ǘ��ԍ�.
    */
    private SceneBase new_Scene( int scene_index )
    {
        switch( scene_index )
        {
        case Scene_Title:
            return new SceneTitle();
        case Scene_Battle:
            return new SceneBattle();
        default:
            return null; //todo:assert
        }
    }
};

