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
            
            //解析位置を進める.
            m_analyze_index = Clamp(0,m_analyze_index,m_msg.length());
            m_count_frame = 0;
            
            //解析文字抽出.
            char const analyze_target = m_msg[m_analyze_index];
            
            //改行だった場合.
            if( analyze_target == '\n' ){
                m_analyze_index++;
                m_draw_msg.push_back("");
                break;
            }
            //タグだった場合.
            if( analyze_target == '[' ){
                //タグ文字抽出.
                std::string const tag_end = "]";
                std::string::size_type const tag_end_index = m_msg.find( tag_end, m_analyze_index );
                std::string const tag = m_msg.substr( m_analyze_index, tag_end_index - m_analyze_index + tag_end.length() );
                m_analyze_index = tag_end_index + tag_end.length();
                //クリック待ち状態へ.
                if( tag == "[click]" ){
                    m_step = Step_WaitClick;
                }
                //画像タグの場合.
                if( tag.find("[image,") != std::string::npos ){
                    //画像番号抽出.
					ImageType const image_type = ImageType_StandFuriru; // 未実装.
                    //表示位置抽出.
					CharacterDrawer::CharaPos const chara_pos = CharacterDrawer::CharaPos_Left; //未実装.
					m_chara_drawer->SetChara(image_type,chara_pos);
                }
                if( tag.find("[right]") != std::string::npos ){
					ImageType const image_type = ImageType_StandSlime; // 未実装.
					CharacterDrawer::CharaPos const chara_pos = CharacterDrawer::CharaPos_Right; //未実装.
					m_chara_drawer->SetChara(image_type,chara_pos);
                }
                //消去.
                if( tag.find("[clear]") != std::string::npos ){
                    m_is_visible = false;
                }
				break;
            }
			//解析終了の場合.
			if(analyze_target=='\0'){
				m_step = Step_End;
				break;
			}
			//それ以外(普通の文字)
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
	    //文字のアウトライン描画.
        DrawFormatString( x-1 , y + i * kaigyou_height , ColorOf(0,0,0) , m_draw_msg.at(i).c_str() );
        DrawFormatString( x+1 , y + i * kaigyou_height , ColorOf(0,0,0) , m_draw_msg.at(i).c_str() );
        DrawFormatString( x , y + i * kaigyou_height-1 , ColorOf(0,0,0) , m_draw_msg.at(i).c_str() );
        DrawFormatString( x , y + i * kaigyou_height+1 , ColorOf(0,0,0) , m_draw_msg.at(i).c_str() );
        //文字描画.
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


