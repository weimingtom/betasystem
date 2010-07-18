
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

void LogPrinter::Impl::Print( std::string log )
{
    std::vector<std::string>::iterator it = m_log_list.begin();
    m_log_list.insert( it , log );
    
    if( m_log_list.size() > m_list_max ){ ; }
}

void Draw()
{
    int const font_size = 16;
    int const log_list_max = 10;
    for( int i = 0 ; i < m_list_max ; i++ )
    {
        DrawString( m_x , m_y + i * font_size  , m_log_list[i] );
    }
}

/**
    ¶¬ŠÖ”.
*/
LogPrinter* new_LogPrinter( int x , int y )
{
    return new LogPrinter::Impl( x , y );
}

