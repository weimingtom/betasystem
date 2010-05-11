import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;

class ScenePlayerTurn extends SceneBase
{
    Graphics g = StaticObjects.getGraphicsInstance();
    InputInfo m_input = StaticObjects.getInputInstance();
    SceneBattleObjects m_objects;
    
    ActionBase[] m_action_list;
    int m_action_list_index;
    
    ScenePlayerTurn( SceneManagerBase scene_manager , SceneBattleObjects objects )
    {
        super( scene_manager );
        m_objects = objects;
        
        m_action_list = new ActionBase[ ActionFactory.ActionType_Num ];
        for( int i = 0 ; i < ActionFactory.ActionType_Num ; i++ )
        {
            m_action_list[i] = ActionFactory.new_Action( i );
        }
    }
    
    public void Init()
    {
    }
    
    public void Update()
    {
        m_input.Update();
        m_objects.Update();
        
        if( m_input.IsTrig( Display.KEY_UP ) )
        {
            m_action_list_index--;
        }
        else if( m_input.IsTrig( Display.KEY_DOWN ) )
        {
            m_action_list_index++;
        }
        else if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            m_action_list[m_action_list_index].Action( m_objects );
            m_objects.EndTurn( BattleSceneManager.Scene_PlayerTurn );
        }
        m_action_list_index = Range.Clamp( 0 , m_action_list_index , ActionFactory.ActionType_Num - 1 );
        
    }
    
    public void Draw()
    {
        m_objects.Draw();
        
        final int base_y = 30;
        final int margin_y = 10;
        for( int i = 0 ; i < ActionFactory.ActionType_Num ; i++ )
        {
            g.drawString( ""+m_action_list[i].m_name , 150 , base_y + i * margin_y);
        }
        g.drawString("¨",130 , base_y + m_action_list_index * margin_y );
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    public void paint( Graphics g ){}
}
