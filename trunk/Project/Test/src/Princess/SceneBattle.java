import com.nttdocomo.ui.*;

/**
    �퓬���.
*/
class SceneBattle extends SceneBase
{
    final int State_PlayerTurn =    0 ;
    final int State_EnemyTurn =     1 ;
    final int State_Win =           2 ;
    final int State_Lose =          3 ;
    final int PlayerX = 140; 
    final int EnemyX = 30;
    
    Graphics g = getGraphics();
    InputInfo m_input = new InputInfo();
    Character m_player = CharacterFactory.New( CharacterFactory.CharaType_Furiru );
    Character m_enemy = CharacterFactory.New( CharacterFactory.CharaType_BlueSlime );
    ImageManager m_image_manager = new ImageManager();
    DamagePrinter m_damage_printer = new DamagePrinter( g );
    
    int m_state = State_PlayerTurn;
    
    //�R���X�g���N�^
    SceneBattle( SceneManagerBase scene_manager_base )
    {
        super( scene_manager_base );
    }
    
    public void Init()
    {
    }
    
    public void Update()
    {
        m_input.Update();
        m_damage_printer.Update();
        
        switch( m_state )
        {
        case State_PlayerTurn:
            UpdatePlayerTurn();
            break;
            
        case State_EnemyTurn:
            UpdateEnemyTurn();
            break;
            
        case State_Win:
            UpdateWin();
            break;
            
        case State_Lose:
            UpdateLose();
            break;
        }
    }
    
    public void Draw()
    {
        g.lock();
        g.clearRect( 0, 0, Display.getWidth() , Display.getHeight() );
        
        g.drawImage( m_image_manager.ImageOf( ImageManager.Image_Base ) , 0 , 0 );
        switch( m_state )
        {
        case State_PlayerTurn:
            DrawEnemy();
            DrawPlayer();
            DrawPlayerStatus( m_player );
            DrawEnemyStatus( m_enemy );
            break;
            
        case State_EnemyTurn:
            DrawEnemy();
            DrawPlayer();
            DrawPlayerStatus( m_player );
            DrawEnemyStatus( m_enemy );
            break;
            
        case State_Win:
            DrawPlayer();
            g.drawString("Win!!" , 40 , 40 );
            break;
            
        case State_Lose:
            DrawEnemy();
            g.drawString("Lose!!" , 40 , 40 );
            break;
        }
        m_damage_printer.Draw();
        
        g.unlock(true);
    }
    
    void DrawEnemy()
    {
        g.drawImage( m_image_manager.ImageOf( ImageManager.Image_Slime ) , 50 , 140 );
    }
    
    void DrawPlayer()
    {
        g.drawImage( m_image_manager.ImageOf( ImageManager.Image_Furiru ) , 115 , 80 );
    }
    
    void DrawPlayerStatus( Character player )
    {
        DrawStatus( player , PlayerX , 10 );
    }
    
    void DrawEnemyStatus( Character enemy )
    {
        DrawStatus( enemy , EnemyX , 10 );
    }
    
    void UpdatePlayerTurn()
    {
        System.out.println("player turn");
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            final int damage = m_player.m_attack;
            m_enemy.m_hp -= damage;
            m_damage_printer.Begin( damage , 60 );
            
            if( m_enemy.m_hp <= 0 )
            {
                m_state = State_Win;
            }else{
                m_state = State_EnemyTurn;
            }
        }
    }
    
    void UpdateEnemyTurn()
    {
        System.out.println("enemy turn");
        final int damage = m_enemy.m_attack;
        m_player.m_hp -= damage;
        m_damage_printer.Begin( damage , 180 );
        if( m_player.m_hp <= 0 )
        {
            m_state = State_Lose;
        }else{
            m_state = State_PlayerTurn;
        }
    }
    
    void UpdateWin()
    {
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            /*
                �ꎞ�I�ɃR�s�y�ɂȂ��Ă��邾���ŁA�X�e�[�W��񂩂�A�����X�^�[�����肷��悤�ɂȂ�ƁA
                ���̏����͖����Ȃ�.
            */
            m_enemy = CharacterFactory.New( CharacterFactory.CharaType_BlueSlime );
            m_state = State_PlayerTurn;
        }
    }
    
    void UpdateLose()
    {
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            m_scene_manager.ChangeScene( PrincessSceneManager.SceneGameOver );
        }
    }
    
    void DrawStatus( Character character , int x , int y )
    {
        g.drawString("m_name:"+character.m_name , x , y +=10 );
        g.drawString("m_hp:"+character.m_hp, x , y +=10  );
        g.drawString("m_attack:"+character.m_attack, x , y +=10  );
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    //���g�p
    public void paint( Graphics g ){}
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
    �摜�f�[�^���Ǘ�����N���X.
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
        
        //���Ԗ����̂ň�U�R�s�y.
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
