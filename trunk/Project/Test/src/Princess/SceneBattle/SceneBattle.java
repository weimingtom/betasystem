import com.nttdocomo.ui.*;

/**
    戦闘画面.
*/
class SceneBattle extends SceneBase
{
    Graphics g = getGraphics();
    BattleSceneManager m_scene_manager = new BattleSceneManager( g );
    
    //コンストラクタ
    SceneBattle( SceneManagerBase scene_manager_base )
    {
        super( scene_manager_base );
    }
    
    public void Init()
    {
        m_scene_manager.ChangeScene( BattleSceneManager.Scene_PlayerTurn );
    }
    
    public void Update()
    {
        m_scene_manager.CurrentScene().Update();
    }
    
    public void Draw()
    {
        g.lock();
        g.clearRect( 0, 0, Display.getWidth() , Display.getHeight() );
        m_scene_manager.CurrentScene().Draw();
        g.unlock(true);
    }
    
    //未使用
    public void paint( Graphics g ){}
}

