import com.nttdocomo.ui.Display;

/**
    入力情報を管理するクラス.
*/
class InputInfo
{
    //! 入力を検出するキー一覧.
    final int[] m_key_type =
    {
        Display.KEY_LEFT,
        Display.KEY_RIGHT,
        Display.KEY_UP,
        Display.KEY_DOWN,
        Display.KEY_SOFT1,
        Display.KEY_SOFT2,
        Display.KEY_SELECT,
    };
    
    //! キー押下フレーム数を保存する.
    int[] m_key_pressed_frame;
    
    //! キー押下フラグ.
    boolean[] m_key_pressed_flag;
    
    /**
        コンストラクタ.
    */
    InputInfo()
    {
        m_key_pressed_frame = new int[ m_key_type.length ];
        m_key_pressed_flag = new boolean[ m_key_type.length ];
    }
    
    /**
        入力情報の更新.
        @note Canvas::processEvent の引数を入れてください.
    */
    public void UpdateInputInfo( int type , int param )
    {
        if( type == Display.KEY_PRESSED_EVENT )
        {
            for( int i = 0 ; i < m_key_type.length ; i++ )
            {
                if( param == m_key_type[i] )
                {
                    m_key_pressed_flag[i] = true;
                }
            }
        }
        else if( type == Display.KEY_RELEASED_EVENT )
        {
            for( int i = 0 ; i < m_key_type.length ; i++ )
            {
                if( param == m_key_type[i] )
                {
                    m_key_pressed_flag[i] = false;
                }
            }
        }
    }
    
    public void Update()
    {
        //フラグを元に押下フレームを加算.
        for( int i = 0 ; i < m_key_type.length ; i++ )
        {
            if( m_key_pressed_flag[i] )
            {
                m_key_pressed_frame[i] ++;
            }else{
                m_key_pressed_frame[i] = 0;
            }
        }
    }
    
    /**
        押下フレーム数の取得.
    */
    public int KeyPressedFrame( int param )
    {
        for( int i = 0 ; i < m_key_type.length ; i++ )
        {
            if( param == m_key_type[i] )
            {
                return m_key_pressed_frame[i];
            }
        }
        return 0;//@todo:assert
    }
    
    /**
        トリガーの取得.
    */
    public boolean IsTrig( int param )
    {
        for( int i = 0 ; i < m_key_type.length ; i++ )
        {
            if( param == m_key_type[i] )
            {
                if( m_key_pressed_frame[i] == 1 ){ return true; }
            }
        }
        return false;
    }
}

