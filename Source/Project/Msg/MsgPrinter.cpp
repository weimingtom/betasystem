#include "MsgPrinter.hpp"

#include "DxLibWrapper/Color.hpp"
#include "System/Range.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"

MsgPrinter::MsgPrinter()
 : m_chara_drawer( new CharacterDrawer() )
{
    Init();
}

MsgPrinter::~MsgPrinter()
{
}

void MsgPrinter::Init()
{
    m_msg = "";
    m_draw_msg.clear();
    m_draw_msg.push_back("");
    m_msg_speed = 1;
    m_count_frame = 0;
    m_analyze_index = 0;
    m_step = Step_Idle;
    m_is_visible = true;
}

void MsgPrinter::Update()
{
    m_chara_drawer->Update();
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
                m_draw_msg.push_back("");
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
                //�摜�^�O�̏ꍇ.
                if( tag.find("[image,") != std::string::npos ){
                    //�摜�ԍ����o.
					ImageType const image_type = ImageType_StandFuriru; // ������.
                    //�\���ʒu���o.
					CharacterDrawer::CharaPos const chara_pos = CharacterDrawer::CharaPos_Left; //������.
					m_chara_drawer->SetChara(image_type,chara_pos);
                }
                if( tag.find("[right]") != std::string::npos ){
					ImageType const image_type = ImageType_StandSlime; // ������.
					CharacterDrawer::CharaPos const chara_pos = CharacterDrawer::CharaPos_Right; //������.
					m_chara_drawer->SetChara(image_type,chara_pos);
                }
                //����.
                if( tag.find("[clear]") != std::string::npos ){
                    m_is_visible = false;
                }
				break;
            }
			//��͏I���̏ꍇ.
			if(analyze_target=='\0'){
				m_step = Step_End;
				break;
			}
			//����ȊO(���ʂ̕���)
            m_draw_msg.at( m_draw_msg.size()-1 ) += analyze_target;
            m_analyze_index++;
        }

        break;
    case Step_WaitClick:
        if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
            m_step = Step_UpdateMsg;
        }
        break;
	case Step_Idle:
		break;
    case Step_End:
        break;
    }
}

void MsgPrinter::Draw() const
{
    if( !m_is_visible ){
        return;
    }

    m_chara_drawer->Draw();

    int const window_top = 370;
    int const outside_margin = 10;
    int const inside_margin = 10;
    DrawBox( outside_margin, window_top, 640-outside_margin, 480-outside_margin, GetColor( 255,255,255 ), TRUE );
    
    int const kaigyou_height = 15;
	for( std::vector<std::string>::size_type i = 0 ; i < m_draw_msg.size() ; i ++ ){
	    int const x = outside_margin + inside_margin;
	    int const y = window_top + inside_margin;
	    //�����̃A�E�g���C���`��.
        DrawFormatString( x-1 , y + i * kaigyou_height , ColorOf(0,0,0) , m_draw_msg.at(i).c_str() );
        DrawFormatString( x+1 , y + i * kaigyou_height , ColorOf(0,0,0) , m_draw_msg.at(i).c_str() );
        DrawFormatString( x , y + i * kaigyou_height-1 , ColorOf(0,0,0) , m_draw_msg.at(i).c_str() );
        DrawFormatString( x , y + i * kaigyou_height+1 , ColorOf(0,0,0) , m_draw_msg.at(i).c_str() );
        //�����`��.
        DrawFormatString( x , y + i * kaigyou_height , ColorOf(255,255,255) , m_draw_msg.at(i).c_str() );
    }
}

void MsgPrinter::SetMsg(std::string msg)
{
    Init();
    m_step = Step_UpdateMsg;
    m_msg = msg;
}

bool MsgPrinter::IsEnd() const
{
    return (m_step == Step_End);
}


