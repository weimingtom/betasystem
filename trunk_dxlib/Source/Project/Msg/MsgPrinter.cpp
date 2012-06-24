#include "MsgPrinter.hpp"

#include "DxLibWrapper/Color.hpp"
#include "System/Range.hpp"

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
    m_msg_speed = 10;
    m_count_frame = 0;
    m_visible_index = 0;
    m_x = 100;
    m_y = 100;
}

void MsgPrinter::Update()
{
    m_count_frame++;
    if( m_count_frame >= m_msg_speed ){
        m_visible_index++;
        m_visible_index= Clamp(0,m_visible_index,m_msg.length());
        m_count_frame = 0;
    }
}

void MsgPrinter::Draw() const
{
    std::string const draw_str = m_msg.substr(0,m_visible_index);
    DrawFormatString( m_x , m_y , ColorOf(0,255,0) , draw_str.c_str() );
}

void MsgPrinter::SetMsg(std::string msg)
{
    Init();
    m_msg = msg;
}


