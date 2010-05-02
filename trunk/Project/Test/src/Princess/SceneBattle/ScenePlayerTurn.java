import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;

class ScenePlayerTurn extends SceneBase
{
    Graphics g = StaticObjects.getGraphicsInstance();
    InputInfo m_input = StaticObjects.getInputInstance();
    
    SceneBattleObjects m_objects;
    
    ScenePlayerTurn( SceneManagerBase scene_manager , SceneBattleObjects objects )
    {
        super( scene_manager );
        m_objects = objects;
    }
    
    public void Init()
    {
    }
    
    public void Update()
    {
        m_input.Update();
        
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            m_scene_manager.ChangeScene( BattleSceneManager.Scene_EnemyTurn );
        }
    }
    
    public void Draw()
    {
        g.lock();
        g.clearRect( 0 , 0  , Display.getWidth() , Display.getHeight() );
        
        g.drawString( "�yPlayerTurn�z " , 50 , 100 );
        g.drawString( "Push SelectKey." , 50 , 120 );
        
        g.unlock(true);
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
