import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Canvas;


class MainCanvas extends Canvas implements Runnable
{
    /**
        ���C�����[�v.
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
    
    // �g�p���Ȃ�.
    public void paint( Graphics g ){}
}

