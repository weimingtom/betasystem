import com.nttdocomo.ui.Display;

/**
    Scene の切り替えを管理するクラス.
*/
class SceneChangeManager
{
    /*
        Scene 管理番号.
    */
    public static final int Scene_Title = 0; //!< タイトル画面.
    public static final int Scene_Battle  = 1; //!< メイン画面.
    
    //! 現在のシーン.
    private SceneBase m_current_scene;
    
    /**
        コンストラクタ.
    */
    SceneChangeManager()
    {
        ChangeScene( Scene_Title );
    }
    
    /**
        現在の Scene を返す関数.
    */
    public SceneBase CurrentScene()
    {
        return m_current_scene ;
    }
    
    /**
        Scene 切り替え関数.
        @param scene_index Scene 管理番号.
    */
    public void ChangeScene( int scene_index )
    {
        m_current_scene = new_Scene( scene_index );
        Display.setCurrent( m_current_scene );
        m_current_scene.Init();
    }
    
    /**
        Scene 管理番号から、 Scene を生成する関数.
        @param scene_index Scene 管理番号.
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

