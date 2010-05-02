import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Canvas;

/**
    ���ʂ��Ďg�p����`��N���X.
    
    Display.setCurrent()�őΏۂƂȂ�N���X�����A��ʕ`�悪���f����Ȃ��̂ŁA
    ��ʕ`��́A�B��̂��̃C���X�^���X�ōs���悤�ɂ���.
    setCurrent�̑Ώۂ����̃N���X�ȊO�͐ݒ肵�Ȃ��悤�ɂ���.
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
    
    // �g�p���Ȃ�.
    public void paint( Graphics g ){}
}

