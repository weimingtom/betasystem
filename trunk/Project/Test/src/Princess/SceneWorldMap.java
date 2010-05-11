import com.nttdocomo.ui.*;

class SceneWorldMap extends SceneBase
{
    Graphics g = StaticObjects.getGraphicsInstance();
    InputInfo m_input = StaticObjects.getInputInstance();
    Image m_image = StaticObjects.getImageManagerInstance().ImageOf( ImageManager.Image_WorldMap );
    
    Stage[] m_stage_list;
    int m_stage_list_index;
    
    //コンストラクタ
    SceneWorldMap( SceneManagerBase scene_manager )
    {
        super( scene_manager );
        
        m_stage_list = new Stage[ StageFactory.StageType_Num ];
        for( int i = 0 ; i < StageFactory.StageType_Num ; i++ )
        {
            m_stage_list[i] = StageFactory.new_Stage( i );
        }
    }
    public void Init()
    {
    }
    public void Update()
    {
        m_input.Update();
        
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            StaticObjects.SetStage( m_stage_list_index );
            m_scene_manager.ChangeScene( PrincessSceneManager.SceneBattle );
        }
        else if( m_input.IsTrig( Display.KEY_UP ) )
        {
            m_stage_list_index--;
        }
        else if( m_input.IsTrig( Display.KEY_DOWN ) )
        {
            m_stage_list_index++;
        }
        m_stage_list_index = Range.Clamp( 0 , m_stage_list_index , StageFactory.StageType_Num - 1  );
    }
    
    public void Draw()
    {
        g.drawImage( m_image , 0 , 0 );
        g.drawString( "Push SelectKey." , 50 , 120 );
        
        final int offset_y = 30;
        for( int i = 0 ; i < StageFactory.StageType_Num ; i++ )
        {
            g.drawString( ""+i+":"+m_stage_list[i].m_name , 20 , i * 20 + offset_y );
        }
        g.drawString( "→" , 0 , m_stage_list_index * 20 + offset_y );
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
