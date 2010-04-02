import com.nttdocomo.ui.*;

/**
    戦闘画面.
*/
class SceneBattle extends SceneBase
{
    final int State_PlayerTurn =    0 ;
    final int State_EnemyTurn =     1 ;
    final int State_Win =           2 ;
    final int State_Lose =          3 ;
    
    Graphics g = getGraphics();
    InputInfo m_input = new InputInfo();
    Character m_player = CharacterFactory.New( CharacterFactory.CharaType_Furiru );
    Character m_enemy = CharacterFactory.New( CharacterFactory.CharaType_BlueSlime );
    ImageManager m_image_manager = new ImageManager();
    
        int m_state = State_PlayerTurn;
    
    //コンストラクタ
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
            DrawStatus( m_player , 140 , 10 );
            DrawStatus( m_enemy , 30 , 10 );
            break;
            
        case State_EnemyTurn:
            DrawEnemy();
            DrawPlayer();
            DrawStatus( m_player , 140 , 10 );
            DrawStatus( m_enemy , 30 , 10 );
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
    
    void UpdatePlayerTurn()
    {
        System.out.println("player turn");
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            m_enemy.m_hp -= m_player.m_attack;
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
        m_player.m_hp -= m_enemy.m_attack;
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
                一時的にコピペになっているだけで、ステージ情報から、モンスターを決定するようになると、
                この処理は無くなる.
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
    
    //未使用
    public void paint( Graphics g ){}
}

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
