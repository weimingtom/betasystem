import com.nttdocomo.ui.*;

class SceneGameOver extends SceneBase
{
    Graphics g = getGraphics();
    InputInfo m_input = new InputInfo();

    //コンストラクタ
    SceneGameOver( SceneManagerBase scene_manager_base )
    {
        super( scene_manager_base );
    }
    
    public void Init()
    {
    }
    
    public void Update()
    {
        m_input.Update();
        if( m_input.IsTrig( Display.KEY_SELECT ) )
        {
            m_scene_manager.ChangeScene( PrincessSceneManager.SceneTitle );
        }
    }
    
    public void Draw()
    {
        g.lock();
        g.clearRect( 0, 0, Display.getWidth() , Display.getHeight() );
        
        g.drawString( "【ゲームオーバー画面】" , 50 , 100 );
        g.drawString( "Push SelectKey." , 50 , 120 );
        
        g.unlock(true);
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    //未使用
    public void paint( Graphics g ){}
}
