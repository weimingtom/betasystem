import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;

class SceneBattle extends SceneBase
{
    Graphics g = getGraphics();
    Character m_player = new Character( "ƒvƒŠƒ€" , 10 , 3 );
    Character m_enemy = new Character( "ƒXƒ‰ƒCƒ€" , 5 , 1 );
    
    public void Init()
    {
    }
    public void Update()
    {
    }
    public void Draw()
    {
        g.lock();
        
        g.clearRect( 0, 0, Display.getWidth() , Display.getHeight() );
        PrintStatus( m_player , 140 , 200 );
        PrintStatus( m_enemy , 30 , 200 );
        
        g.unlock(true);
    }
    
    void PrintStatus( Character character , int x , int y )
    {
        g.drawString("m_name:"+character.m_name , x , y +=10 );
        g.drawString("m_hp:"+character.m_hp, x , y +=10  );
        g.drawString("m_attack:"+character.m_hp, x , y +=10  );
    }
    
    public void paint( Graphics g ){}
}
