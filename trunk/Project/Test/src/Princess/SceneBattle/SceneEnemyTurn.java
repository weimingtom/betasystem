import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Display;

class SceneEnemyTurn extends SceneBase
{
    Graphics g;
    InputInfo m_input = StaticObjects.getInputInstance();
    SceneBattleObjects m_objects;
    
    SceneEnemyTurn( SceneManagerBase scene_manager , SceneBattleObjects objects )
    {
        super( scene_manager );
        m_objects = objects;
        g = StaticObjects.getGraphicsInstance();
    }
    
    public void Init()
    {
    }
    
    public void Update()
    {
        m_input.Update();
        m_objects.Update();
        
        m_objects.ActionAttack( false );
        m_objects.EndTurn( BattleSceneManager.Scene_EnemyTurn );
    }
    
    public void Draw()
    {
        m_objects.Draw();
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
    
}

