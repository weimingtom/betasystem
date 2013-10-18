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
        Step_Win,
        Step_Lose,
        Step_Escape,
        Step_End,
    };
private:
    void UpdateSelectAction();
    void UpdateDrawAction();
    void UpdateTurnEnd();
    //! 敵の攻撃
    void EnemyAttack();
    //! ターンの実行.
    void PlayTurn();
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
    //! 状態判定.
    bool IsEndBattle() const;
private:
    Step mStep;
    int mBattleCommand;
    std::auto_ptr<Avater> mEnemyAvater;
    std::auto_ptr<Avater> mPlayerAvater;
    std::auto_ptr<LogPrinter> mLogPrinter;
};

#endif // STATE_BATTLE_HPP__
