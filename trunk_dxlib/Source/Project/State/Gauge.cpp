#include "Gauge.hpp"


Gauge::Gauge( int max )
 : m_value_max(max)
 , m_value(0)
 , m_pause(false)
 , m_add_value(2)
 , m_critlcal_range(1)
{
}

Gauge::~Gauge()
{
}

void Gauge::Update()
{
    if( m_pause ){return;}
	m_value += m_add_value;
	if( m_value >= m_value_max ){
		m_add_value = -2;
	}
	if( m_value <= 0){
		m_add_value = 2;
	}
}

