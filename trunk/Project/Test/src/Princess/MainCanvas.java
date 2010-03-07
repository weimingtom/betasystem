import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Canvas;


class MainCanvas extends Canvas implements Runnable
{
    /**
        メインループ.
    */
    public void run()
    {
        while( true )
        {
            SceneBase current_scene = SceneChangeManager.getInstance().CurrentScene();
            current_scene.Update();
            current_scene.Draw();
            
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

