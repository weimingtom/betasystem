#include "DxLibWrapper/LogPrinter.hpp"

#include <vector>
#include "DxLibWrapper/Color.hpp"

class LogPrinter::Impl : public LogPrinter
{
public:
    Impl( int x , int y );
    ~Impl();
    
public:
    void Print( std::string log );
    void Draw();
    
private:
    std::vector< std::string > m_log_list;
    int m_x;
    int m_y;
    static int const m_list_max = 16;
};

LogPrinter::Impl::Impl( int x , int y )
 : m_x(x)
 , m_y(y)
{
}

LogPrinter::Impl::~Impl()
{
}

void LogPrinter::Impl::Print( std::string log )
{
    std::vector<std::string>::iterator it = m_log_list.begin();
    m_log_list.insert( it , log );
    
    if( m_log_list.size() > m_list_max ){ m_log_list.pop_back(); }
}

void LogPrinter::Impl::Draw()
{
    int const font_size = 16;
    int const log_list_max = 10;
	for( std::string::size_type i = 0 ; i < m_log_list.size() ; i++ )
    {
        DrawFormatString(
            m_x + 1 , m_y + i * font_size + 1 ,
            ColorOf() ,
            "%s" , m_log_list[i].c_str() );
        DrawFormatString(
            m_x , m_y + i * font_size ,
            ColorOf(255,255,255) ,
            "%s" , m_log_list[i].c_str() );
    }
}

/**
    ¶¬ŠÖ”.
*/
LogPrinter* new_LogPrinter( int x , int y )
{
    return new LogPrinter::Impl( x , y );
}

