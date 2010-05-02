import com.nttdocomo.ui.*;

/**
    �퓬���.
*/
class SceneBattle extends SceneBase
{
    Graphics g;
    BattleSceneManager m_scene_manager = new BattleSceneManager();
    
    //�R���X�g���N�^
    SceneBattle( SceneManagerBase scene_manager_base )
    {
        super( scene_manager_base );
        g = StaticObjects.getGraphicsInstance();
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
    
    //���g�p
    public void paint( Graphics g ){}
}

