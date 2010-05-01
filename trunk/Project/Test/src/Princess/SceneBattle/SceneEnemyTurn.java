import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;

class SceneEnemyTurn extends SceneBase
{
    Graphics g = getGraphics();
    InputInfo m_input_info = new InputInfo();
    SceneBattleObjects m_objects;
    
    SceneEnemyTurn( SceneManagerBase scene_manager , SceneBattleObjects objects )
    {
        super( scene_manager );
        m_objects = objects;
    }
    public void Init()
    {
    }
    public void Update()
    {
        m_input_info.Update();
        
        if( m_input_info.IsTrig( Display.KEY_SELECT ) )
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
        m_input_info.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
