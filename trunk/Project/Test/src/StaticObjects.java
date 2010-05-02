import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Canvas;

/**
    ���ʂ��Ďg�p����I�u�W�F�N�g�Q.
*/
class StaticObjects extends Canvas
{
    static private StaticObjects  m_instance = null;
    
    /**
        Display.setCurrent�Ŏw��ł���Frame�͈�ŁA
        ��ʑJ�ږ���Frame�����\�����ƁA����q���Frame�̕`�悪��肭�����Ȃ��B
        ����āA�S�Ă̕`��͂���Graphics��ʂ��ĕ`�悷�鎖�ɂ���.
    */
    Graphics m_graphics;
    
    /**
        Display.setCurrent��processEvent���ݒ肳���̂ŁA��ނȂ������ɕێ�.
    */
    InputInfo m_input;
    
    private StaticObjects()
    {
        m_graphics = getGraphics();
        m_input = new InputInfo();
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
    
    // �g�p���Ȃ�.
    public void paint( Graphics g ){}
}

