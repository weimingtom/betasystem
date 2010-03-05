import com.nttdocomo.ui.Graphics;

class SceneBattle extends SceneBase
{
    Graphics g = getGraphics();
    int m_frame;
    
    public void Init()
    {
        m_frame = 0;
    }
    public void Update()
    {
        m_frame++;
    }
    public void Draw()
    {
        g.drawString("frame"+m_frame , 10 , 10 );
    }
    
    public void paint( Graphics g ){}
}
