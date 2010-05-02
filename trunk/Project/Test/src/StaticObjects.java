import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Canvas;

/**
    プロジェクト全体で共通して使用するオブジェクト群.
*/
class StaticObjects extends Canvas
{
    static private StaticObjects  m_instance = null;
    
    /**
        Display.setCurrentで指定できるFrameは一つで、
        画面遷移毎にFrameを作る構成だと、入れ子状のFrameの描画が上手くいかない。
        よって、全ての描画はこのGraphicsを通して描画する事にする.
    */
    Graphics m_graphics;
    
    /**
        Display.setCurrentでprocessEventも設定されるので、やむなくここに保持.
    */
    InputInfo m_input;
    
    /**
        画像管理クラス.
    */
    ImageManager m_image_manager;
    
    private StaticObjects()
    {
        m_graphics = getGraphics();
        m_input = new InputInfo();
        m_image_manager = new ImageManager();
    }
    
    static Graphics getGraphicsInstance()
    {
        createInstance();
        return m_instance.m_graphics;
    }
    
    static InputInfo getInputInstance()
    {
        createInstance();
        return m_instance.m_input;
    }
    
    static ImageManager getImageManagerInstance()
    {
        createInstance();
        return m_instance.m_image_manager;
    }
    
    private static void createInstance()
    {
        if( m_instance == null )
        {
            m_instance = new StaticObjects();
            Display.setCurrent( m_instance );
        }
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    // 使用しない.
    public void paint( Graphics g ){}
}

