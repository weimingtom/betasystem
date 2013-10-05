#include "Gauge.hpp"

#include "System/Range.hpp"


Gauge::Gauge( int max )
 : m_value_max(max)
 , m_value(0)
 , m_pause(false)
 , m_sub_value(1)
{
}

Gauge::~Gauge()
{
}

void Gauge::Update( bool is_clicked )
{
    if( m_pause ){return;}
    
    if( is_clicked ){
        m_value += 20;
    }
	m_value -= m_sub_value;
	m_value = Clamp(0,m_value,m_value_max);
}

