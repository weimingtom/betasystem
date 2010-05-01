import com.nttdocomo.ui.*;

/**
    SceneBattle において、共通して使用するオブジェクト群.
*/
class SceneBattleObjects
{
    Graphics m_graphics;
    DamagePrinter m_damage_printer;
    ImageManager m_image_manager = new ImageManager();
    Character m_player = CharacterFactory.New( CharacterFactory.CharaType_Furiru );
    Character m_enemy = CharacterFactory.New( CharacterFactory.CharaType_BlueSlime );
    
    SceneBattleObjects( Graphics g )
    {
        m_graphics = g;
        m_damage_printer = new DamagePrinter( g );
    }
    
    
    void DrawStatus( Character character , int x , int y )
    {
        m_graphics.drawString("m_name:"+character.m_name , x , y +=10 );
        m_graphics.drawString("m_hp:"+character.m_hp, x , y +=10  );
        m_graphics.drawString("m_attack:"+character.m_attack, x , y +=10  );
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
    Graphics m_graphics;
    
    DamagePrinter( Graphics g )
    {
        m_graphics = g;
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
            m_graphics.drawString( ""+m_damage , m_x , m_y );
            m_graphics.drawString( ""+m_damage , m_x , m_y+1 );
        }
    }
};

/**
    画像データを管理するクラス.
*/
class ImageManager
{
    static final int Image_Base = 0;
    static final int Image_Furiru = 1;
    static final int Image_Slime = 2;
    static final int Image_Num = 3;
    
    Image[] m_image_list;
    
    ImageManager()
    {
        m_image_list = new Image[ Image_Num ];
        
        //時間無いので一旦コピペ.
        MediaImage media_image_base = MediaManager.getImage( "resource:///image/battle_base.gif" );
        MediaImage media_image_enemy = MediaManager.getImage( "resource:///image/green_slime.gif" );
        MediaImage media_image_player = MediaManager.getImage( "resource:///image/furiru.gif" );
        try{
            media_image_base.use();
            media_image_enemy.use();
            media_image_player.use();
        }catch( Exception e ){
            System.out.println("error!!-media_image use failed");
        }
        m_image_list[ Image_Base ] = media_image_base.getImage();
        m_image_list[ Image_Slime ] = media_image_enemy.getImage();
        m_image_list[ Image_Furiru ] = media_image_player.getImage();
    }
    
    Image ImageOf( int image_index )
    {
        return m_image_list[ image_index ];
    }
}
