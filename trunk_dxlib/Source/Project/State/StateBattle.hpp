#ifndef include_guard_dab9ac90_e1c4_4e8c_bed1_df0275db9b24
#define include_guard_dab9ac90_e1c4_4e8c_bed1_df0275db9b24

class StateManagerBase;
class ScrollBackground;
#include "System/StateBase.hpp"
#include <memory>


class StateBattle : public StateBase
{
public:
    StateBattle( StateManagerBase& manager );
    
public:
    void Update();
    void Draw();

private:
	/**
		State 内での遷移.
	*/
	enum Step
	{
		Step_DecideMeter1,
		Step_DecideMeter2,
		Step_WaitDash, //!< ダッシュ前のアクション.
		Step_Dash,
		Step_Result,
	};
	
private:
	void UpdateMeter( int meter_index );
	void DecideMeter();
	void SetStep( Step step );
	void StepWaitDash();
	void DashPlayer();

private:
    StateManagerBase& m_manager;
    int m_meter[2];
    int m_add_meter;
    Step m_step;
    float m_player_x;
    float m_player_speed;
    std::auto_ptr<ScrollBackground> m_background;
    int m_frame;
};

#endif

