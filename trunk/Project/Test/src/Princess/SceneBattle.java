import com.nttdocomo.ui.*;

class SceneBattle extends SceneBase
{
    Graphics g = getGraphics();
    InputInfo m_input = new InputInfo();
    Character m_player = CharacterFactory.New( CharacterFactory.CharaType_Furiru );
    Character m_enemy = CharacterFactory.New( CharacterFactory.CharaType_BlueSlime );
    Image m_image;
    
    final int State_PlayerTurn =    0 ;
    final int State_EnemyTurn =     1 ;
    final int State_Win =           2 ;
    final int State_Lose =          3 ;
    
    int m_state = State_PlayerTurn;
    
    //�R���X�g���N�^
    SceneBattle( SceneManagerBase scene_manager_base )
    {
        super( scene_manager_base );
    }
    
    public void Init()
    {
        MediaImage media_image = MediaManager.getImage( "resource:///image/hoge.gif" );
        try{
            media_image.use();
        }catch( Exception e ){
            System.out.println("error!!-media_image use failed");
        }
        m_image = media_image.getImage();
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
        
        
        switch( m_state )
        {
        case State_PlayerTurn:
            g.drawImage( m_image , 0 , 0 );
            DrawStatus( m_player , 140 , 10 );
            DrawStatus( m_enemy , 30 , 10 );
            break;
            
        case State_EnemyTurn:
            g.drawImage( m_image , 0 , 0 );
            DrawStatus( m_player , 140 , 10 );
            DrawStatus( m_enemy , 30 , 10 );
            break;
            
        case State_Win:
            g.drawImage( m_image , 0 , 0 );
            g.drawString("Win!!" , 40 , 40 );
            break;
            
        case State_Lose:
            g.drawImage( m_image , 0 , 0 );
            g.drawString("Lose!!" , 40 , 40 );
            break;
        }
                
        g.unlock(true);
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
            m_scene_manager.ChangeScene( PrincessSceneManager.SceneTitle );
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
