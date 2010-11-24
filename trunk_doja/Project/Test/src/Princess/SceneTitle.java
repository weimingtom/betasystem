import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Image;

class SceneTitle extends SceneBase
{
    private Graphics g = StaticObjects.getGraphicsInstance();
    private InputInfo m_input = StaticObjects.getInputInstance();
    private ImageManager m_image_manager = StaticObjects.getImageManagerInstance();
    private Image m_image = m_image_manager.ImageOf( ImageManager.Image_Title );

    //コンストラクタ
    SceneTitle( SceneManagerBase scene_manager )
    {
        super( scene_manager );
        System.out.println("SceneTitle::SceneTitle()");
    }
    public void Init()
    {
    }
    public void Update()
    {
        System.out.println("SceneTitle::Update()");
        
        m_input.Update();
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            m_scene_manager.ChangeScene( PrincessSceneManager.SceneWorldMap );
        }
    }
    public void Draw()
    {
        g.drawImage( m_image , 20 , 20 );
        g.drawString( "Push SelectKey." , 50 , 120 );
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
