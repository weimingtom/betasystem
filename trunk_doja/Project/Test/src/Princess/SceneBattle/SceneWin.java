import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;

class SceneWin extends SceneBase
{
    Graphics g = StaticObjects.getGraphicsInstance();
    InputInfo m_input = StaticObjects.getInputInstance();
    SceneBattleObjects m_objects;
    
    SceneWin( SceneManagerBase scene_manager , SceneBattleObjects objects )
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
            m_objects.EndTurn( BattleSceneManager.Scene_Win );
        }
    }
    
    public void Draw()
    {
        m_objects.Draw();
        g.drawString("�yWin�z" , 100 , 100 );
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
    
}

