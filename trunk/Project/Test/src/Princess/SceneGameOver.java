import com.nttdocomo.ui.*;

class SceneGameOver extends SceneBase
{
    Graphics g = StaticObjects.getGraphicsInstance();
    InputInfo m_input = StaticObjects.getInputInstance();
    AudioPresenter m_audio_presenter = AudioPresenter.getAudioPresenter();
    private ImageManager m_image_manager = StaticObjects.getImageManagerInstance();
    private Image m_image = m_image_manager.ImageOf( ImageManager.Image_GameOver );
    
    //コンストラクタ
    SceneGameOver( SceneManagerBase scene_manager_base )
    {
        super( scene_manager_base );
    }
    
    public void Init()
    {
        MediaSound media_sound = MediaManager.getSound("resource:///sound/gameover.mld");
        try{
            media_sound.use();
        } catch ( Exception e ) {
            System.out.println("throw exception in media_sound.use() ");
        }
        m_audio_presenter.setSound( media_sound );
        m_audio_presenter.play();
    }
    
    public void Update()
    {
        m_input.Update();
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            m_scene_manager.ChangeScene( PrincessSceneManager.SceneTitle );
            m_audio_presenter.stop();
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
    
    //未使用
    public void paint( Graphics g ){}
}

