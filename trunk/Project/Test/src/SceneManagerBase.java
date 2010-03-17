import com.nttdocomo.ui.Display;

/**
    シーン管理クラス.
*/
abstract class SceneManagerBase
{
    //! 現在のシーン.
    private SceneBase m_current_scene;
    
    /**
        現在の Scene を返す関数.
    */
    public SceneBase CurrentScene()
    {
        return m_current_scene;
    }
    
    /**
        Scene 切り替え関数.
        @param scene_index Scene 管理番号.
    */
    public void ChangeScene( int scene_index )
    {
        System.out.println("ChangeScene()");
        
        m_current_scene = new_Scene( scene_index );
        Display.setCurrent( m_current_scene );
        m_current_scene.Init();
    }
    
    /**
        Scene 管理番号から Scene を生成する関数.
        @param scene_index Scene 管理番号.
    */
    abstract SceneBase new_Scene( int scene_index );
};

