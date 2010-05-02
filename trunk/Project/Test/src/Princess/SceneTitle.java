import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;

class SceneTitle extends SceneBase
{
    Graphics g;
    InputInfo m_input_info = new InputInfo();
    
    //コンストラクタ
    SceneTitle( SceneManagerBase scene_manager )
    {
        super( scene_manager );
        g = StaticGraphics.getInstance();
        
        System.out.println("SceneTitle::SceneTitle()");
    }
    public void Init()
    {
    }
    public void Update()
    {
        System.out.println("SceneTitle::Update()");
        
        m_input_info.Update();
        if( m_input_info.IsTrig( Display.KEY_SELECT ) )
        {
            m_scene_manager.ChangeScene( PrincessSceneManager.SceneWorldMap );
        }
    }
    public void Draw()
    {
        System.out.println("SceneTitle::Draw()");
        
        g.lock();
        g.drawString( "【タイトル画面】 " , 50 , 100 );
        g.drawString( "Push SelectKey." , 50 , 120 );
        g.unlock(true);
    }
    
    public void processEvent( int type , int param )
    {
        m_input_info.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
