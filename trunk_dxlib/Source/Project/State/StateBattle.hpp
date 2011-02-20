#ifndef include_guard_dab9ac90_e1c4_4e8c_bed1_df0275db9b24
#define include_guard_dab9ac90_e1c4_4e8c_bed1_df0275db9b24

class StateManagerBase;
class ScrollBackground;
class Camera;
class AnimTexture;
#include <memory>
#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "Project/Enemy.hpp"
#include "Project/Item.hpp"

class StateBattle : public StateBase
{
public:
    StateBattle( StateManagerBase& manager );
    
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
	};
private:
	static int const EnemyNum = 400;
	
private:
	void UpdateMeter( int meter_index );
	void SetStep( Step step );
	void InitStepWaitDash();
	void StepWaitDash();
	void DashPlayer();
	void DrawDebug() const;
	void DrawGauge() const;
	void UpdateCommon();
	void InitResult();
	void DrawBack() const;
	void InitStepDecideMeter();
	void StepDecideMeter();
    void UseItem();

private:
    StateManagerBase& m_manager;
    int m_meter[2];
    int m_add_meter; //!< メーターの増加量.
    Step m_step;
    Vector2 m_player_pos;
    float m_player_speed;
    std::auto_ptr<ScrollBackground> m_background;
    int m_frame;
    std::auto_ptr<Camera> m_camera;
    Enemy m_enemy[ EnemyNum ];
    int m_player_power;
    std::auto_ptr<AnimTexture> m_player_texture;
    ItemType m_get_item; //!< 取得したアイテムの一時置き場.
    int m_player_life;
    int m_target_meter;
    int m_meter_max;
};

#endif

