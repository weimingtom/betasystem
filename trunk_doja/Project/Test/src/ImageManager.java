import com.nttdocomo.ui.*;

/**
    �摜�f�[�^���Ǘ�����N���X.
*/
class ImageManager
{
    static final int Image_Base         = 0;
    static final int Image_Player       = 1;
    static final int Image_Slime        = 2;
    static final int Image_WorldMap     = 3;
    static final int Image_Sky          = 4;
    static final int Image_Title        = 5;
    static final int Image_GameOver     = 6;
    static final int Image_Num          = 7;
    
    Image[] m_image_list;
    String[] m_image_name;
    
    ImageManager()
    {
        InitImageName();
        
        m_image_list = new Image[ Image_Num ];
        
        for( int i = 0 ; i < Image_Num ; i++ )
        {
            MediaImage media_image = MediaManager.getImage( m_image_name[i] );
            try{
                media_image.use();
            }catch( Exception e ){
                System.out.println("error!!-media_image use failed");
            }
            m_image_list[ i ] = media_image.getImage();
        }
    }
    
    void InitImageName()
    {
        m_image_name = new String[ Image_Num ];
        m_image_name[ Image_Base ]      = "resource:///image/battle_base.gif";
        m_image_name[ Image_Slime ]     = "resource:///image/green_slime.gif";
        m_image_name[ Image_Player ]    = "resource:///image/furiru.gif";
        m_image_name[ Image_WorldMap ]  = "resource:///image/worldmap.gif";
        m_image_name[ Image_Sky ]       = "resource:///image/sky.gif";
        m_image_name[ Image_Title ]     = "resource:///image/title.gif";
        m_image_name[ Image_GameOver ]  = "resource:///image/gameover.gif";
    }
    
    Image ImageOf( int image_index )
    {
        return m_image_list[ image_index ];
    }
}