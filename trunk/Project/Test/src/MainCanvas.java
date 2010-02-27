import com.nttdocomo.ui.Canvas;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Frame;
import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Image;
import com.nttdocomo.ui.MediaImage; 
import com.nttdocomo.ui.MediaManager;


class MainCanvas extends Canvas implements Runnable
{
    SceneBase m_scene_base = new SceneTitle();
    
    MainCanvas()
    {
        Display.setCurrent( m_scene_base );
    }
    
    public void run()
    {
        m_scene_base.Init();
        while( true )
        {
            m_scene_base.Update();
            m_scene_base.Draw();
            
            try
            {
                Thread.sleep(100);
            }catch(Exception e){
                
            } 
        }
    }
    
    // Žg—p‚µ‚È‚¢.
    public void paint( Graphics g ){}
}

