import com.nttdocomo.ui.Canvas;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Frame;
import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Image;
import com.nttdocomo.ui.MediaImage; 
import com.nttdocomo.ui.MediaManager;

class SampleCanvas extends Canvas
{
    private int m_frame;
    Graphics g = getGraphics();

    SampleCanvas()
    {
    }
    
    public void Update()
    {
        m_frame++;
    }
    
    public void Draw()
    {
        g.lock();
        
        g.clearRect( 0,0,getWidth(),getHeight());
        g.drawString( "SampleCanvas" + m_frame , 10 , 10 );
        
        g.unlock( true );
    }
    
    public void paint( Graphics g )
    {
    }
}

