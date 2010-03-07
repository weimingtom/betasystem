import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;

class SceneBattle extends SceneBase
{
    Graphics g = getGraphics();
    InputInfo m_input = new InputInfo();
    
    Character m_player = new Character( "ƒvƒŠƒ€" , 10 , 3 );
    Character m_enemy = new Character( "ƒXƒ‰ƒCƒ€" , 5 , 1 );
    
    final int State_PlayerTurn =    0 ;
    final int State_EnemyTurn =     1 ;
    final int State_Win =           2 ;
    final int State_Lose =          3 ;
    
    int m_state = State_PlayerTurn;
    
    public void Init()
    {
    }
    
    public void Update()
    {
        m_input.Update();
        
        switch( m_state )
        {
        case State_PlayerTurn:
            System.out.println("player turn");
            if( m_input.KeyPressedFrame( Display.KEY_SELECT ) == 1 )
            {
                m_enemy.m_hp -= m_player.m_attack;
                if( m_enemy.m_hp <= 0 )
                {
                    m_state = State_Win;
                }else{
                    m_state = State_EnemyTurn;
                }
            }
            break;
            
        case State_EnemyTurn:
            System.out.println("enemy turn");
            m_player.m_hp -= m_enemy.m_attack;
            if( m_player.m_hp <= 0 )
            {
                m_state = State_Lose;
            }else{
                m_state = State_PlayerTurn;
            }
            break;
            
        case State_Win:
            SceneChangeManager.getInstance().ChangeScene( SceneChangeManager.Scene_Battle );
            break;
            
        case State_Lose:
            
            break;
        }
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
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
     
    public void paint( Graphics g ){}
}
