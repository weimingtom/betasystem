import com.nttdocomo.ui.*;

class SceneWorldMap extends SceneBase
{
    Graphics g = getGraphics();
    InputInfo m_input_info = new InputInfo();
    Image m_image;
    
    //�R���X�g���N�^
    SceneWorldMap( SceneManagerBase scene_manager )
    {
        super( scene_manager );
    }
    public void Init()
    {
        //@todo:�R�s�y�c�AImageManager�쐬�҂�.
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
        m_input_info.Update();
        
        if( m_input_info.IsTrig( Display.KEY_SELECT ) )
        {
            m_scene_manager.ChangeScene( PrincessSceneManager.SceneBattle );
        }
    }
    public void Draw()
    {
        g.lock();
        g.clearRect( 0 , 0  , Display.getWidth() , Display.getHeight() );
        
        g.drawImage( m_image , 0 , 0 );
        g.drawString( "�y���[���h�}�b�v��ʁz " , 50 , 100 );
        g.drawString( "Push SelectKey." , 50 , 120 );
        
        g.unlock(true);
    }
    
    public void processEvent( int type , int param )
    {
        m_input_info.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
