#ifndef include_41221b54_6f0f_4e4d_9b0c_2659ed1c8124
#define include_41221b54_6f0f_4e4d_9b0c_2659ed1c8124

/**
	�K�E�Q�[�W�Ǘ��N���X.
*/
class SpecialGauge
{
public:
	SpecialGauge();
	virtual ~SpecialGauge();
public:
	void Add(){ if(mGaugeNum<GaugeMax){ mGaugeNum++; } }
	void Reset(){ mGaugeNum=0; }
	void Draw() const;
	int Num() const{ return mGaugeNum; };
	bool CanUseSpecial() const{ return (mGaugeNum == GaugeMax); }
	bool IsFull() const { return (mGaugeNum == GaugeMax); }
private:
	static int const GaugeMax = 5;
	int mGaugeNum;
};

#endif // include_41221b54_6f0f_4e4d_9b0c_2659ed1c8124

