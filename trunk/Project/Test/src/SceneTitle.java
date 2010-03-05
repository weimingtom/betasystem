import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;

class SceneTitle extends SceneBase
{
    Graphics g = getGraphics();
    InputInfo m_input_info = new InputInfo();
    int m_frame;
    
    public void Init()
    {
        m_frame = 0;
    }
    public void Update()
    {
        m_input_info.Update();
        m_frame++;
    }
    public void Draw()
    {
        g.lock();
        g.clearRect( 0 , 0  , Display.getWidth() , Display.getHeight() );
        
        g.drawString("select="+m_input_info.KeyPressedFrame( Display.KEY_SELECT ) , 10 , 10 );
        g.drawString("left="+m_input_info.KeyPressedFrame( Display.KEY_LEFT ) , 10 , 20 );
        
        g.unlock(true);
    }
    
    public void processEvent( int type , int param )
    {
        m_input_info.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
