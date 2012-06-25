#include "MsgPrinter.hpp"

#include "DxLibWrapper/Color.hpp"
#include "System/Range.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"

MsgPrinter::MsgPrinter()
{
    Init();
}

MsgPrinter::~MsgPrinter()
{
}

void MsgPrinter::Init()
{
    m_msg = "";
    m_draw_msg = "";
    m_msg_speed = 1;
    m_count_frame = 0;
    m_analyze_index = 0;
    m_x = 100;
    m_y = 100;
    m_step = Step_UpdateMsg;
}

void MsgPrinter::Update()
{
    switch( m_step )
    {
    case Step_UpdateMsg:
        m_count_frame++;
        if( m_count_frame >= m_msg_speed ){
            //��͈ʒu��i�߂�.
            m_analyze_index = Clamp(0,m_analyze_index,m_msg.length());
            m_count_frame = 0;
            
            //��͕������o.
            char const analyze_target = m_msg[m_analyze_index];
            
            //���s�������ꍇ.
            if( analyze_target == '\n' ){
                m_analyze_index++;
                break;
            }
            //�^�O�������ꍇ.
            if( analyze_target == '[' ){
                //�^�O�������o.
                std::string const tag_end = "]";
                std::string::size_type const tag_end_index = m_msg.find( tag_end, m_analyze_index );
                std::string const tag = m_msg.substr( m_analyze_index, tag_end_index - m_analyze_index + tag_end.length() );
                m_analyze_index = tag_end_index + tag_end.length();
                //�N���b�N�҂���Ԃ�.
                if( tag == "[click]" ){
                    m_step = Step_WaitClick;
                }
				break;
            }
			//��͏I���̏ꍇ.
			if(analyze_target=='\0'){
				m_step = Step_Idle;
				break;
			}
			//����ȊO.
            m_draw_msg+=analyze_target;
            m_analyze_index++;
        }

        break;
    case Step_WaitClick:
        if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
            m_step = Step_UpdateMsg;
        }
        break;
	case Step_Idle:
		int hoge = 0;
		break;
    }
}

void MsgPrinter::Draw() const
{
    DrawFormatString( m_x , m_y , ColorOf(0,255,0) , m_draw_msg.c_str() );
}

void MsgPrinter::SetMsg(std::string msg)
{
    Init();
    m_msg = msg;
}


