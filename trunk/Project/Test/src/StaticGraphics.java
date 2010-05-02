import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Canvas;

/**
    共通して使用する描画クラス.
    
    Display.setCurrent()で対象となるクラスしか、画面描画が反映されないので、
    画面描画は、唯一つのこのインスタンスで行うようにする.
    setCurrentの対象もこのクラス以外は設定しないようにする.
*/
class StaticGraphics extends Canvas
{
    static private StaticGraphics m_instance = null;
    Graphics g;
    
    private StaticGraphics()
    {
        g = getGraphics();
    }
    
    static Graphics getInstance()
    {
        if( m_instance == null )
        {
            m_instance = new StaticGraphics();
            Display.setCurrent( m_instance );
        }
        return m_instance.g;
    }
    
    // 使用しない.
    public void paint( Graphics g ){}
}

