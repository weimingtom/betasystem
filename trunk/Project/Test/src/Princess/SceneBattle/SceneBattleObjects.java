import com.nttdocomo.ui.*;

/**
    SceneBattle �ɂ����āA���ʂ��Ďg�p����I�u�W�F�N�g�Q.
*/
class SceneBattleObjects
{
    Graphics g;
    DamagePrinter m_damage_printer;
    Character m_player = CharacterFactory.New( CharacterFactory.CharaType_Furiru );
    Character m_enemy = CharacterFactory.New( CharacterFactory.CharaType_BlueSlime );
    
    SceneBattleObjects()
    {
        g = StaticObjects.getGraphicsInstance();
        m_damage_printer = new DamagePrinter();
    }
    
    
    void DrawStatus( Character character , int x , int y )
    {
        g.drawString("m_name:"+character.m_name , x , y +=10 );
        g.drawString("m_hp:"+character.m_hp, x , y +=10  );
        g.drawString("m_attack:"+character.m_attack, x , y +=10  );
    }
}

/**
    �_���[�W��`�悷��N���X.
*/
class DamagePrinter
{
    final int default_y = 70;
    int m_x;
    int m_y;
    int m_damage;
    Graphics g;
    
    DamagePrinter()
    {
        g = StaticObjects.getGraphicsInstance();
    }
    
    void Begin( int damage , int x )
    {
        m_x = x;
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
