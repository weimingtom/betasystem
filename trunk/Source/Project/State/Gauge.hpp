#ifndef include_gauge_hpp
#define include_gauge_hpp

/**
    �퓬��ʂŎg�p����Q�[�W�B
    �X�V���ɃQ�[�W����������B
*/
class Gauge
{
public:
    Gauge( int max );
    ~Gauge();

public:
    void Update( bool is_clicked );
    void SetPause(bool is_pause){ m_pause = is_pause; }
    void SetValue(int value){ m_value = value;}
    int GetValue() const{ return m_value; }
    void SetMax(int value_max){ m_value_max = value_max;}
    int GetMax() const { return m_value_max; }

private:
    int m_value_max;
    int m_value;
    bool m_pause;
    int m_sub_value;
};


#endif // include_gauge_hpp
