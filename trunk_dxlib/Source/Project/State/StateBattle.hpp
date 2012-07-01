#ifndef include_guard_dab9ac90_e1c4_4e8c_bed1_df0275db9b24
#define include_guard_dab9ac90_e1c4_4e8c_bed1_df0275db9b24

class StateManagerBase;
class ScrollBackground;
class Camera;
class AnimTexture;
class Gauge;
class PlayerLife;
class SpecialGauge;
class BreakEnemyCounter;
#include <memory>
#include <vector>
#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "Project/Enemy.hpp"
#include "Project/Item.hpp"
#include "Project/Stage.hpp"
#include "Gauge.hpp"
#include "boost/shared_ptr.hpp"

class StateBattle : public StateBase
{
public:
    StateBattle( StateManagerBase& manager );
    virtual ~StateBattle();
    
public:
    void Update();
    void Draw() const;

private:
	/**
		State 内での遷移.
	*/
	enum Step
	{
		Step_DecideMeter,
		Step_WaitDash, //!< ダッシュ前のアクション.
		Step_Dash,
		Step_DashEnd, //!< ダッシュ終了.
		Step_Result,
		Step_Clear,
	};
	
private:
	void UpdateMeter( int meter_index );
	void SetStep( Step step );
	void InitStepWaitDash();
	void StepWaitDash();
	void InitStepSpecial();
	void StepSpecial();
	void StepDash();
	void DrawDebug() const;
	void DrawDashGauge() const;
	void DrawStepSpecial() const;
	void UpdateCommon();
	void InitResult();
	void DrawBack() const;
	void InitStepDecideMeter();
	void CancelDecideMeter();
	void StepDecideMeter();
    void UseItem();
    void UseItem( ItemType type );
    int RemainEnemy() const;
    void GetItem();
    void DrawItem() const;
    void UpdateHiScore();
	void InitEnemy();
	void UpdateDebug();
    void DrawGauge( int x, int y, Gauge const& gauge) const;
    void PlaySound( Gauge const& gauge );
    bool LotteryAddSpecialGauge() const;

private:
    StateManagerBase& m_manager;
    Step m_step;
    Vector2 m_player_pos;
    std::auto_ptr<ScrollBackground> m_background;
    int m_frame;
    std::auto_ptr<Camera> m_camera;
    std::vector<boost::shared_ptr<Enemy>> m_enemy;
    int m_player_power;
    std::auto_ptr<AnimTexture> m_player_texture;
    std::auto_ptr<PlayerLife> mPlayerLife;
    int m_target_meter;
    std::auto_ptr<BreakEnemyCounter> mBreakEnemyCounter;
    std::auto_ptr<SpecialGauge> mSpecialGauge;
    StageInfo const m_stage_info;
    std::auto_ptr<Gauge> m_gauge[2];
    bool m_is_debug_draw;
};

#endif

