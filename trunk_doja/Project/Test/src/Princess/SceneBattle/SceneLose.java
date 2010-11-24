import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;

class SceneLose extends SceneBase
{
    Graphics g = StaticObjects.getGraphicsInstance();
    InputInfo m_input = StaticObjects.getInputInstance();
    SceneBattleObjects m_objects;
    
    SceneLose(
        SceneManagerBase scene_manager ,
        SceneBattleObjects objects )
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
        m_objects.Update();
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            m_objects.EndTurn( BattleSceneManager.Scene_Lose );
        }
    }
    
    public void Draw()
    {
        m_objects.Draw();
        g.drawString("ÅyLoseÅz" , 100 , 100 );
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
