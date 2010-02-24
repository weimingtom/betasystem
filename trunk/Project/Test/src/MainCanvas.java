import com.nttdocomo.ui.Canvas;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Frame;
import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Image;
import com.nttdocomo.ui.MediaImage; 
import com.nttdocomo.ui.MediaManager;

class MainCanvas extends Canvas implements Runnable
{
    private int m_frame;
    private Image m_image;
    Graphics g = getGraphics();

    MainCanvas()
    {
        MediaImage media_image = MediaManager.getImage( "resource:///futami.gif" );
        try{
            media_image.use();
        }catch( Exception e ){
            System.out.println("error!!-media_image use failed");
        }
        m_image = media_image.getImage();
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
        g.drawImage( m_image , 100 , 100 );
        
        g.unlock( true );
    }
    
    public void paint( Graphics g )
    {
    }
}

