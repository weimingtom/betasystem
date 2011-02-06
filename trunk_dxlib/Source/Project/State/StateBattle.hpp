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
		Step_DecideMeter,
		Step_Dash,
		Step_Result,
	};
	
private:
	void UpdateMeter();
	void DecideMeter();
	void SetStep( Step step );
	void DashPlayer();

private:
    StateManagerBase& m_manager;
    int m_meter;
    int m_add_meter;
    Step m_step;
    int m_player_x;
    int m_move_result; //!< 最終地点.
    std::auto_ptr<ScrollBackground> m_background;
};

#endif

