/**
    ”wŒi•`‰æƒNƒ‰ƒX.
*/
class Background
{
    int m_frame;
    Graphics g = StaticObjects.getGraphicsInstance();
    ImageManager m_image_manager = StaticObjects.getImageManagerInstance();
    Image m_image_base = m_image_manager.ImageOf( ImageManager.Image_Base );
    Image m_image_sky = m_image_manager.ImageOf( ImageManager.Image_Sky );
    
    void Update()
    {
        m_frame++;
        if( m_frame >= m_image_sky.getWidth() )
        {
            m_frame = 0 ;
        }
    }
    
    void Draw()
    {
        g.drawImage(
            m_image_sky , 0 - m_frame , 0 );
        g.drawImage(
            m_image_sky ,
            m_image_sky.getWidth() - m_frame  , 0 );
        g.drawImage( m_image_base , 0 , 0 );
    }
};
