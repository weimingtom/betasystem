/**
    Scene �̐؂�ւ����Ǘ�����N���X.
*/
class SceneChangingManager
{
    /**
        �R���X�g���N�^.
    */
    SceneManager()
    {
        m_current_scene = new_Scene( scene_default );
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
        case scene_title:
            return new SceneTitle();
        case scene_main:
            return new SceneMain();
        default:
        }
    }
    
    /*
        Scene �Ǘ��ԍ�.
    */
    public static final int scene_title =   0; //!< �^�C�g�����.
    public static final int scene_main =    1; //!< ���C�����.
    public static final int scene_default = scene_title; //!< �f�t�H���g.
    
    //! ���݂̃V�[��.
    private SceneBase m_current_scene;
    
};

