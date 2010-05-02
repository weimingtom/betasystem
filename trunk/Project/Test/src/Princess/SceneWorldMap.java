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
        //@todo:コピペ…、ImageManager作成待ち.
        MediaImage media_image = MediaManager.getImage( "resource:///image/worldmap.gif" );
        try{
            media_image.use();
        }catch( Exception e ){
            System.out.println("error!!-media_image use failed");
        }
        m_image = media_image.getImage();
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
