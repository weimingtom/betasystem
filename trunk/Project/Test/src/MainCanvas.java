import com.nttdocomo.ui.Canvas;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Frame;
import com.nttdocomo.ui.Display;

class MainCanvas extends Canvas implements Runnable
{
    Graphics g = getGraphics();
    int m_frame;

    MainCanvas()
    {
    }
    
    public void run()
    {
        while( true )
        {
            Update();
            Draw();
            
            try
            {
                Thread.sleep(100);//100msec‘Ò‚Â  
            }catch(Exception e){
                
            } 
        }
    }
    
    public void Update()
    {
        m_frame++;
    }
    
    public void Draw()
    {
        g.lock();
        
        g.clearRect( 0,0,getWidth(),getHeight());
        g.drawString( "hoge" + m_frame , 10 , 10 );
        
        g.unlock( true );
    }
    
    public void paint( Graphics g )
    {
    }
}

