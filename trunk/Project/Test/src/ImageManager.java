import com.nttdocomo.ui.*;

/**
    画像データを管理するクラス.
*/
class ImageManager
{
    static final int Image_Base         = 0;
    static final int Image_Furiru       = 1;
    static final int Image_Slime        = 2;
    static final int Image_WorldMap     = 3;
    static final int Image_Num          = 4;
    
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
        m_image_name[ Image_Base ] = "resource:///image/battle_base.gif";
        m_image_name[ Image_Slime ] = "resource:///image/green_slime.gif";
        m_image_name[ Image_Furiru ] = "resource:///image/furiru.gif";
        m_image_name[ Image_WorldMap ] = "resource:///image/worldmap.gif";
    }
    
    Image ImageOf( int image_index )
    {
        return m_image_list[ image_index ];
    }
}
