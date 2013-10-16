#ifndef STATE_BATTLE_HPP__
#define STATE_BATTLE_HPP__

#include <memory>
#include "System/StateBase.hpp"
#include "Project/Avater/Avater.hpp"

class StateBattle : public StateBase
{
public:
    StateBattle();
    ~StateBattle();
public:
	void Update();
	void Draw() const;
private:
    //! 戦闘コマンド.
    enum BattleAction{
        BattleAction_Attack,
        BattleAction_Pray,
        BattleAction_Away,
        BattleAction_Num,
    };
    //! 遷移状態.
    enum Step{
    	Step_SelectAction,	//!< 行動選択.
    	Step_ProcAction,	//!< 行動計算.
    	Step_DrawAction,	//!< 行動の表示（見た目を再生）.
    	Step_TurnEnd,		//!< ターン終了.
    };
private:
    void UpdateSelectAction();
    void UpdateProcAction();
    void UpdateDrawAction();
    void UpdateTurnEnd();
private:
    Step mStep;
    int mIndex;
    std::auto_ptr<Avater> mEnemyAvater;
};

#endif // STATE_BATTLE_HPP__
