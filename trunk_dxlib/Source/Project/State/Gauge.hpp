#ifndef include_gauge_hpp
#define include_gauge_hpp

/**
    戦闘画面で使用するゲージ。
    更新時にゲージが増減する。
    クリティカルゾーンとグッドゾーンの判定が出来る。
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
    bool IsCritical() const { return ( m_value >= m_value_max - m_critlcal_range ); }
    int GetGood() const{ return ( m_critlcal_range * 3 ); }
    bool IsGood() const{ return ( !IsCritical() && m_value >= m_value_max - GetGood() ); }

private:
    int m_value_max;
    int m_value;
    bool m_pause;
    int m_add_value;
    int m_critlcal_range;
};


#endif // include_gauge_hpp

