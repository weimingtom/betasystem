#include "StateBattle.hpp"

#include "Project/Singleton/SaveData.hpp"
#include "Project/Singleton/PlayerParam.hpp"
#include "System/Range.hpp"
#include "System/ArraySize.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/EnemyParam.hpp"

StateBattle::StateBattle()
 : mStep( Step_SelectAction )
 , mBattleCommand( BattleCommand_Attack )
{
    gEnemyParam = EnemyParamOf(EnemyID_0);
    mEnemyAvater.reset( new Avater(gEnemyParam.mEquipList) );
}

StateBattle::~StateBattle()
{
}

void StateBattle::Update()
{
    switch( mStep )
    {
    case Step_SelectAction:
        UpdateSelectAction();
        break;
	case Step_End:
		break;
    }
}

void StateBattle::UpdateSelectAction()
{
    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){ --mBattleCommand; }
    else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){ ++mBattleCommand; }
    mBattleCommand = Clamp( 0, mBattleCommand, BattleCommand_Num - 1 );
    
    if( KeyInput()->IsTrig( InputKey::Type_Enter ) ){
        Action( static_cast<BattleCommand>(mBattleCommand) );
    }
}

void StateBattle::UpdateDrawAction()
{
}

void StateBattle::UpdateTurnEnd()
{
}

void StateBattle::Action( BattleCommand command )
{
    switch( command )
    {
    case BattleCommand_Attack:
        Attack();
        break;
    case BattleCommand_Pray:
        Pray();
        break;
    case BattleCommand_Escape:
        Escape();
        break;
    }

    if( JudgeBattleEnd() == Status_Continue ){
        Attack();//敵の攻撃
    }
    
    switch( JudgeBattleEnd() )
    {
    case Status_Continue:
        ProcContinue();
        break;
    case Status_Win:
        ProcWin();
        break;
    case Status_Lose:
        ProcLose();
        break;
    case Status_Escape:
        ProcEscape();
        break;
    }
}

void StateBattle::Attack()
{
    if( JudgeAttackMiss() ){
        //ミスした。
        return;
    }
    
    // charaparamからcharaparamへダメージを与える.
}

void StateBattle::Pray()
{
    //敵のドロップ率を上げる.
}

void StateBattle::Escape()
{
    // 成功抽選をする
    
    // 逃げに成功する.
}

bool StateBattle::JudgeAttackMiss()
{
    return false;
}

StateBattle::Status StateBattle::JudgeBattleEnd()
{
    //逃げが成功している.

    //プレイヤーが死んでる.
    
    //敵が死んでる.
    
    //続行.
    return Status_Continue;
}

void StateBattle::ProcContinue()
{
}

void StateBattle::ProcWin()
{
}

void StateBattle::ProcLose()
{
}

void StateBattle::ProcEscape()
{
}

void StateBattle::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "戦闘画面");
    
    DrawFormatString( 0 , 50+mBattleCommand*15 , GetColor(0,255,0) , "→");

    char const* action_name[BattleCommand_Num] =
    {
        "攻撃",
        "祈る",
        "逃げる",
    };
    for( int i = 0; i < BattleCommand_Num ; i++ ){
        DrawFormatString( 20 , 50+i*15 , GetColor(0,255,0) , action_name[i]);
    }

    DrawFormatString( 120 , 50 ,    GetColor(0,255,0) , "Enemy:hp[%d],attack[%d]",gEnemyParam.mHp,gEnemyParam.mAttack);
    
    mEnemyAvater->Draw(200,200);
}

