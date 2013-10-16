#ifndef STATE_BATTLE_HPP__
#define STATE_BATTLE_HPP__

#include <memory>
#include "System/StateBase.hpp"
#include "Project/Avater/Avater.hpp"
#include "DxLibWrapper/LogPrinter.hpp"

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
        BattleCommand_Escape,
        BattleCommand_Num,
    };
    //! 遷移状態.
    enum Step{
    	Step_SelectAction,	//!< 行動選択.
    	Step_Escape,
    };
    //! 状態.
    enum Status{
        Status_Continue,     //!< 続行.
        Status_Win,         //!< 勝利.
        Status_Lose,        //!< 敗北.
        Status_Escape,      //!< 逃げ.
    };
private:
    void UpdateSelectAction();
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
    //! 逃げ判定.
    bool JudgeEscape() const;
    //! ミス判定.
    bool JudgeAttackMiss() const;
    //! 戦闘終了判定.
    Status JudgeBattleEnd();
    void ProcContinue();
    void ProcWin();
    void ProcLose();
    void ProcEscape();
private:
    Step mStep;
    int mBattleCommand;
    std::auto_ptr<Avater> mEnemyAvater;
    std::auto_ptr<LogPrinter> mLogPrinter;
};

#endif // STATE_BATTLE_HPP__
