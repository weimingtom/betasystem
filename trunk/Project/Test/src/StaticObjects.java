import com.nttdocomo.ui.Display;
import com.nttdocomo.ui.Graphics;
import com.nttdocomo.ui.Canvas;

/**
    �v���W�F�N�g�S�̂ŋ��ʂ��Ďg�p����I�u�W�F�N�g�Q.
*/
class StaticObjects extends Canvas
{
    static private StaticObjects  m_instance = null;
    
    /**
        Display.setCurrent�Ŏw��ł���Frame�͈�ŁA
        ��ʑJ�ږ���Frame�����\�����ƁA����q���Frame�̕`�悪��肭�����Ȃ��B
        ����āA�S�Ă̕`��͂���Graphics��ʂ��ĕ`�悷�鎖�ɂ���.
    */
    Graphics m_graphics;
    
    /**
        Display.setCurrent��processEvent���ݒ肳���̂ŁA��ނȂ������ɕێ�.
    */
    InputInfo m_input;
    
    /**
        �摜�Ǘ��N���X.
    */
    ImageManager m_image_manager;
    
    /**
        �퓬���s���X�e�[�W.
        SceneWorldMap �� SceneBattle ���܂����f�[�^.
        �����������ʓ|�Ȃ̂� Static �ɕێ����Ă݂�.
    */
    Stage m_stage;
    
    private StaticObjects()
    {
        m_graphics = getGraphics();
        m_input = new InputInfo();
        m_image_manager = new ImageManager();
    }
    
    static Graphics getGraphicsInstance()
    {
        createInstance();
        return m_instance.m_graphics;
    }
    
    static InputInfo getInputInstance()
    {
        createInstance();
        return m_instance.m_input;
    }
    
    static ImageManager getImageManagerInstance()
    {
        createInstance();
        return m_instance.m_image_manager;
    }
    
    private static void createInstance()
    {
        if( m_instance == null )
        {
            m_instance = new StaticObjects();
            Display.setCurrent( m_instance );
        }
    }
    
    static Stage getStage()
    {
        return m_instance.m_stage;
    }
    
    static void SetStage( int stage_num )
    {
        m_instance.m_stage = StageFactory.new_Stage( stage_num );
    }
    
    public void processEvent( int type , int param )
    {
        m_input.UpdateInputInfo( type , param );
    }
    
    // �g�p���Ȃ�.
    public void paint( Graphics g ){}
}
