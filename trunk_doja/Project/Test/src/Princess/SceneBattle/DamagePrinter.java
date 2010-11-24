
/**
    ダメージを描画するクラス.
*/
class DamagePrinter
{
    final int player_x = 180;
    final int enemy_x =  20;
    final int default_y = 70;
    int m_x;
    int m_y;
    int m_damage;
    Graphics g;
    
    DamagePrinter()
    {
        g = StaticObjects.getGraphicsInstance();
    }
    
    void Begin( int damage , boolean is_player )
    {
        if( is_player )
        {
            m_x = enemy_x;
        }else{
            m_x = player_x;
        }
        m_y = default_y;
        m_damage = damage;
    }
    
    void Update()
    {
        m_y--;
    }
    
    void Draw()
    {
        if( m_y > default_y - 10 )
        {
            g.drawString( ""+m_damage , m_x , m_y );
            g.drawString( ""+m_damage , m_x , m_y+1 );
        }
    }
};
