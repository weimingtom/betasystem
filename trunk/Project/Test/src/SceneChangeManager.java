/**
    Scene の切り替えを管理するクラス.
*/
class SceneChangingManager
{
    /**
        コンストラクタ.
    */
    SceneManager()
    {
        m_current_scene = new_Scene( scene_default );
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
        case scene_title:
            return new SceneTitle();
        case scene_main:
            return new SceneMain();
        default:
        }
    }
    
    /*
        Scene 管理番号.
    */
    public static final int scene_title =   0; //!< タイトル画面.
    public static final int scene_main =    1; //!< メイン画面.
    public static final int scene_default = scene_title; //!< デフォルト.
    
    //! 現在のシーン.
    private SceneBase m_current_scene;
    
};

