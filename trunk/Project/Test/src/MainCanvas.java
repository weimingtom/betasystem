import com.nttdocomo.ui.Canvas;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Frame;
import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Image;
import com.nttdocomo.ui.MediaImage; 
import com.nttdocomo.ui.MediaManager;


class MainCanvas extends Canvas implements Runnable
{
    SampleCanvas m_current_canvas = new SampleCanvas();
    
    MainCanvas()
    {
        Display.setCurrent( m_current_canvas );
    }
    
    public void run()
    {
        while( true )
        {
            m_current_canvas.Update();
            m_current_canvas.Draw();
            
            try
            {
                Thread.sleep(100);
            }catch(Exception e){
                
            } 
        }
    }
    
    public void paint( Graphics g )
    {
    }
}

