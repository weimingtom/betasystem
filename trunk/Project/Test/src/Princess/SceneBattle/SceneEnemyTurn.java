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
        
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            m_scene_manager.ChangeScene( BattleSceneManager.Scene_PlayerTurn);
        }
    }
    public void Draw()
    {
        g.lock();
        g.clearRect( 0 , 0  , Display.getWidth() , Display.getHeight() );
        
        g.drawString( "ÅyEnemyTurnÅz " , 50 , 100 );
        g.drawString( "Push SelectKey." , 50 , 120 );
        
        g.unlock(true);
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
