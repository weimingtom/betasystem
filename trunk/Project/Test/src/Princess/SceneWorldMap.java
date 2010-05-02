import com.nttdocomo.ui.*;

class SceneWorldMap extends SceneBase
{
    Graphics g = StaticObjects.getGraphicsInstance();
    InputInfo m_input = StaticObjects.getInputInstance();
    Image m_image;
    
    //コンストラクタ
    SceneWorldMap( SceneManagerBase scene_manager )
    {
        super( scene_manager );
    }
    public void Init()
    {
        m_image = StaticObjects.getImageManagerInstance().ImageOf( ImageManager.Image_WorldMap );
    }
    public void Update()
    {
        m_input.Update();
        
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            m_scene_manager.ChangeScene( PrincessSceneManager.SceneBattle );
        }
    }
    public void Draw()
    {
        g.lock();
        g.clearRect( 0 , 0  , Display.getWidth() , Display.getHeight() );
        
        g.drawImage( m_image , 0 , 0 );
        g.drawString( "【ワールドマップ画面】 " , 50 , 100 );
        g.drawString( "Push SelectKey." , 50 , 120 );
        
        g.unlock(true);
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
