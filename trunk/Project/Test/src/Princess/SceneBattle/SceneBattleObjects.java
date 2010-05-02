import com.nttdocomo.ui.*;

/**
    SceneBattle において、共通して使用するオブジェクト群.
*/
class SceneBattleObjects
{
    Graphics g = StaticObjects.getGraphicsInstance();
    DamagePrinter m_damage_printer = new DamagePrinter();
    Character m_player = CharacterFactory.New( CharacterFactory.CharaType_Furiru );
    Character m_enemy = CharacterFactory.New( CharacterFactory.CharaType_BlueSlime );
    
    ImageManager m_image_manager = StaticObjects.getImageManagerInstance();
    Image m_image_player = m_image_manager.ImageOf( ImageManager.Image_Player );
    Image m_image_base = m_image_manager.ImageOf( ImageManager.Image_Base );
    Image m_image_enemy = m_image_manager.ImageOf( ImageManager.Image_Slime );
    
    void DrawBattleScreen()
    {
        g.drawImage( m_image_base , 0 , 00 );
        g.drawImage( m_image_player , 120 , 80 );
        g.drawImage( m_image_enemy , 40 , 150 );
        DrawStatus( m_player , 120 , 10 );
        DrawStatus( m_enemy , 20 , 10 );
    }
    
    private void DrawStatus( Character character , int x , int y )
    {
        g.drawString("m_name:"+character.m_name , x , y +=10 );
        g.drawString("m_hp:"+character.m_hp, x , y +=10  );
        g.drawString("m_attack:"+character.m_attack, x , y +=10  );
    }
}

/**
    ダメージを描画するクラス.
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
