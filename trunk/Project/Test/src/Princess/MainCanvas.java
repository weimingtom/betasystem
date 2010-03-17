import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Canvas;


class MainCanvas extends Canvas implements Runnable
{
    PrincessSceneManager m_scene_manager = new PrincessSceneManager();
    
    //���C�����[�v.
    public void run()
    {
        m_scene_manager.ChangeScene( PrincessSceneManager.SceneTitle );
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

