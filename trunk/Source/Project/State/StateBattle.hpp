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
#include "Project/Msg/MsgPrinter.hpp"
#include "Gauge.hpp"
#include "boost/shared_ptr.hpp"
#include "DxLibWrapper/LogPrinter.hpp"

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
		State ���ł̑J��.
	*/
	enum Step
	{
	    Step_PreTalk,
		Step_DecideMeter,
		Step_WaitDash, //!< �_�b�V���O�̃A�N�V����.
		Step_Dash,
		Step_DashEnd, //!< �_�b�V���I��.
		Step_Result,
		Step_Battle_Player,
		Step_Battle_Enemy,
		Step_OpenGate,
		Step_TreasureBox,
		Step_Clear,
	};
	
private:
	void UpdateMeter( int meter_index );
	void SetStep( Step step );
	void InitPreTalk();
	void InitStepWaitDash();
	void StepWaitDash();
	void InitStepSpecial();
	void StepSpecial();
	void StepDash();
	void StepBattlePlayer();
	void DrawDebug() const;
	void DrawDashGauge() const;
	void DrawStepSpecial() const;
	void UpdateCommon();
	void InitResult();
	void DrawBack() const;
	void InitStepDecideMeter();
	void CancelDecideMeter();
	void StepDecideMeter();
    bool UseItem();
    void UseItem( ItemType type );
    void GetItem();
    void DrawItem() const;
    void UpdateHiScore();
	void UpdateDebug();
    void DrawGauge( int x, int y) const;
    bool LotteryAddSpecialGauge() const;
private:
    bool RecoverMagic();
    void LevelUp();
private:
    StateManagerBase& m_manager;
    Step m_step;
    Vector2 m_player_pos;
    std::auto_ptr<ScrollBackground> m_background;
    int m_frame;
    std::auto_ptr<Camera> m_camera;
    int m_player_power;
    std::auto_ptr<AnimTexture> m_player_texture;
    std::auto_ptr<Enemy> m_enemy;
    std::auto_ptr<PlayerLife> mPlayerLife;
    std::auto_ptr<BreakEnemyCounter> mBreakEnemyCounter;
    StageInfo const m_stage_info;
    bool m_is_debug_draw;
    std::auto_ptr<MsgPrinter> m_msg_printer;
    std::auto_ptr<LogPrinter> m_log_printer;
    int m_kyuukei_frame;
};

#endif
