import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Canvas;


class MainCanvas extends Canvas implements Runnable
{
    SceneChangeManager m_scene_manager = new SceneChangeManager();
    
    /**
        ���C�����[�v.
    */
    public void run()
    {
        while( true )
        {
            m_scene_manager.CurrentScene().Update();
            m_scene_manager.CurrentScene().Draw();
            
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

