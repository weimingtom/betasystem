import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Canvas;


class MainCanvas extends Canvas implements Runnable
{
    PrincessSceneManager m_scene_manager = new PrincessSceneManager();
    Graphics g = StaticObjects.getGraphicsInstance();
    
    //メインループ.
    public void run()
    {
        m_scene_manager.ChangeScene( PrincessSceneManager.SceneTitle );
        while( true )
        {
            m_scene_manager.CurrentScene().Update();
            {
                g.lock();
                g.clearRect( 0 , 0  , Display.getWidth() , Display.getHeight() );
                
                m_scene_manager.CurrentScene().Draw();
                
                g.unlock(true);
            }
            
            try
            {
                Thread.sleep(100);
            }catch(Exception e){
                
            } 
        }
    }
    
    // 使用しない.
    public void paint( Graphics g ){}
}

