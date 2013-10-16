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
    enum BattleCommand{
        BattleCommand_Attack,
        BattleCommand_Pray,
        BattleCommand_Away,
        BattleCommand_Num,
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
    //! 戦闘コマンド実行.
    void Action( BattleCommand command );
    //! コマンド「攻撃」の処理.
    void Attack();
    //! コマンド「祈る」の処理.
    void Pray();
    //! コマンド「逃げる」の処理.
    void Escape();
    //! ミス判定.
    bool JudgeAttackMiss();
private:
    Step mStep;
    int mBattleCommand;
    std::auto_ptr<Avater> mEnemyAvater;
};

#endif // STATE_BATTLE_HPP__
