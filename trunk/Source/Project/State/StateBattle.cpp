#include "StateBattle.hpp"

#include <sstream>
#include "Project/Singleton/SaveData.hpp"
#include "Project/Singleton/PlayerParam.hpp"
#include "System/Range.hpp"
#include "System/ArraySize.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/EnemyParam.hpp"

StateBattle::StateBattle()
 : mStep( Step_SelectAction )
 , mBattleCommand( BattleCommand_Attack )
 , mLogPrinter( new_LogPrinter(400,300) )
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
	case Step_Win:
        break;
	case Step_Lose:
        break;
	case Step_Escape:
		break;
    }
}

void StateBattle::UpdateSelectAction()
{
    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){ --mBattleCommand; }
    else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){ ++mBattleCommand; }
    mBattleCommand = Clamp( 0, mBattleCommand, BattleCommand_Num - 1 );
    
    if( KeyInput()->IsTrig( InputKey::Type_Enter ) ){
        PlayTurn();
    }
}

void StateBattle::PlayTurn()
{
	Action( static_cast<BattleCommand>(mBattleCommand) );
    if( !IsEndBattle() ){
        EnemyAttack();
    }
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
}

void StateBattle::Escape()
{
    mLogPrinter->Print("逃げるを選択した。");
    if( JudgeEscape() ){
        mLogPrinter->Print("逃げ出した。");
        mStep = Step_Escape;
        return;
    }else{
        mLogPrinter->Print("しかし回りこまれてしまった。");
    }
}

void StateBattle::EnemyAttack()
{
    mLogPrinter->Print("敵の攻撃。");
    if( JudgeAttackMiss() ){
        mLogPrinter->Print("ミスした。");
        return;
    }
    int const damage = gEnemyParam.mAttack;
	std::stringstream ss;
    ss << damage << "のダメージ";
    mLogPrinter->Print( ss.str() );
    gPlayerParam.mHP -= damage;

    if( gPlayerParam.mHP <= 0 ){
        mStep = Step_Lose;
    }
}

void StateBattle::Attack()
{
    mLogPrinter->Print("攻撃を選択した。");
    if( JudgeAttackMiss() ){
        mLogPrinter->Print("ミスした。");
        return;
    }
    int const damage = gPlayerParam.mAttack;
	std::stringstream ss;
    ss << damage << "のダメージ";
    mLogPrinter->Print( ss.str() );
    gEnemyParam.mHP -= damage;

    if( gEnemyParam.mHP <= 0 ){
        mLogPrinter->Print("敵を倒した");
        mStep = Step_Win;
        return;
    }
}

void StateBattle::Pray()
{
    mLogPrinter->Print("祈った。");
    mLogPrinter->Print("ドロップ率が上昇した。");
    gEnemyParam.mDropPercent *= 2;
}

bool StateBattle::JudgeEscape() const
{
    int const rand_num = GetRand(100);
    return ( rand_num < 30 );
}

bool StateBattle::JudgeAttackMiss() const
{
    int const rand_num = GetRand(100);
    return ( rand_num > 90 );
}

bool StateBattle::IsEndBattle() const
{
    return( mStep != Step_SelectAction );
}

void StateBattle::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "戦闘画面");
    

    char const* action_name[BattleCommand_Num] =
    {
        "攻撃",
        "祈る",
        "逃げる",
    };
    DrawFormatString( 0 , 50+mBattleCommand*15 , GetColor(0,255,0) , "→");
    for( int i = 0; i < BattleCommand_Num ; i++ ){
        DrawFormatString( 20 , 50+i*15 , GetColor(0,255,0) , action_name[i]);
    }

    DrawFormatString( 120 , 50 ,    GetColor(0,255,0) , "Enemy:hp[%d],attack[%d]",gEnemyParam.mHP,gEnemyParam.mAttack);
    
    mEnemyAvater->Draw(200,200);

    mLogPrinter->Draw();
}

