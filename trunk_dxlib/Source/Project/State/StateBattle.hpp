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
		Step_DecideMeter,
		Step_WaitDash, //!< �_�b�V���O�̃A�N�V����.
		Step_Dash,
		Step_DashEnd, //!< �_�b�V���I��.
		Step_Result,
		Step_Clear,
		Step_Special, //!< �K�E�Z�g�p.
	};
private:
	static int const EnemyNum = 1000;
	
private:
	void UpdateMeter( int meter_index );
	void SetStep( Step step );
	void InitStepWaitDash();
	void StepWaitDash();
	void StepDash();
	void DrawDebug() const;
	void DrawCircleGauge() const;
	void UpdateCommon();
	void InitResult();
	void DrawBack() const;
	void InitStepDecideMeter();
	void StepDecideMeter();
    void UseItem();
    void UseItem( ItemType type );
    int RemainEnemy() const;
    int DigitOf(int num,int digit) const;
    void DrawBreakNum() const;
    void GetItem();
    void DrawItem() const;
    void UpdateHiScore();

private:
    StateManagerBase& m_manager;
    int m_meter[2];
    int m_add_meter; //!< ���[�^�[�̑�����.
    Step m_step;
    Vector2 m_player_pos;
    float m_player_speed;
    std::auto_ptr<ScrollBackground> m_background;
    int m_frame;
    std::auto_ptr<Camera> m_camera;
    Enemy* m_enemy[ EnemyNum ];
    int m_player_power;
    std::auto_ptr<AnimTexture> m_player_texture;
    int m_player_life;
    int m_target_meter;
    int m_meter_max;
    int m_break_num; //!< ������.
    int m_special_power_max;
    int m_special_power;
    int m_special_random; //!<�K�E�Q�[�W�����܂�m��.
    int m_critical_range; //!< �N���e�B�J���ƔF�߂���͈�.
};

#endif

