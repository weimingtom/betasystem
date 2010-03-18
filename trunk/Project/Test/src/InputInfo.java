import com.nttdocomo.ui.Display;

/**
    ���͏����Ǘ�����N���X.
*/
class InputInfo
{
    //! ���͂����o����L�[�ꗗ.
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
    
    //! �L�[�����t���[������ۑ�����.
    int[] m_key_pressed_frame;
    
    //! �L�[�����t���O.
    boolean[] m_key_pressed_flag;
    
    /**
        �R���X�g���N�^.
    */
    InputInfo()
    {
        m_key_pressed_frame = new int[ m_key_type.length ];
        m_key_pressed_flag = new boolean[ m_key_type.length ];
    }
    
    /**
        ���͏��̍X�V.
        @note Canvas::processEvent �̈��������Ă�������.
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
        //�t���O�����ɉ����t���[�������Z.
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
        �����t���[�����̎擾.
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
        �g���K�[�̎擾.
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

