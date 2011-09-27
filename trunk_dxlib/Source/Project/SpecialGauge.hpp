#ifndef include_41221b54_6f0f_4e4d_9b0c_2659ed1c8124
#define include_41221b54_6f0f_4e4d_9b0c_2659ed1c8124

/**
	必殺ゲージ管理クラス.
*/
class SpecialGauge
{
public:
	SpecialGauge();
	virtual ~SpecialGauge();
public:
	void Add(){ mGaugeNum++; }
	void Reset(){ mGaugeNum=0; }
	void Draw() const;
private:
	static int const GaugeMax = 5;
	int mGaugeNum;
};

#endif // include_41221b54_6f0f_4e4d_9b0c_2659ed1c8124

