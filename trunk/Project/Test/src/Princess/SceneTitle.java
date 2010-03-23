import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;

class SceneTitle extends SceneBase
{
    Graphics g = getGraphics();
    InputInfo m_input_info = new InputInfo();
    
    //�R���X�g���N�^
    SceneTitle( SceneManagerBase scene_manager )
    {
        super( scene_manager );
    }
    public void Init()
    {
    }
    public void Update()
    {
        m_input_info.Update();
        
        if( m_input_info.KeyPressedFrame( Display.KEY_SELECT ) == 1 )
        {
            m_scene_manager.ChangeScene( PrincessSceneManager.SceneBattle );
        }
    }
    public void Draw()
    {
        g.lock();
        g.clearRect( 0 , 0  , Display.getWidth() , Display.getHeight() );
        
        g.drawString( "�^�C�g�����. " , 10 , 10 );
        g.drawString( "�Z���N�g�L�[�ŁA�o�g����ʂ�." , 10 , 20 );
        
        g.unlock(true);
    }
    
    public void processEvent( int type , int param )
    {
        m_input_info.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}