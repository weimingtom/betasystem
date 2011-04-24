#ifndef include_gauge_hpp
#define include_gauge_hpp

/**
    �퓬��ʂŎg�p����Q�[�W�B
    �X�V���ɃQ�[�W����������B�N���e�B�J���]�[��������B
*/
class Gauge
{
public:
    Gauge();
    ~Gauge();

public:
    void Update();
    void SetPause(bool is_pause){ m_pause = is_pause; }
    void SetValue(int value){ m_value = value;}
    int GetValue() const{ return m_value; }
    void SetMax(int value_max){ m_value_max = value_max;}
    int GetMax() const { return m_value_max; }
    void SetCritical(int critical_range){ m_critlcal_range = critical_range; }
    int GetCritical() const { return m_critlcal_range; }
    bool IsCritical(){ return ( m_value >= m_value_max - m_critlcal_range ); }

private:
    int m_value_max;
    int m_value;
    bool m_pause;
    int m_add_value;
    int m_critlcal_range;
};


#endif // include_gauge_hpp

