#include "StateBattle.hpp"

#include "Project/Singleton/SaveData.hpp"
#include "Project/Singleton/PlayerParam.hpp"
#include "System/Range.hpp"
#include "System/ArraySize.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/EnemyParam.hpp"

StateBattle::StateBattle()
 : mStep( Step_SelectAction )
 , mIndex(0)
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
    case Step_ProcAction:
        UpdateProcAction();
        break;
    case Step_DrawAction:
        UpdateDrawAction();
        break;
    case Step_TurnEnd:
        UpdateTurnEnd();
        break;
    }
}

void StateBattle::UpdateSelectAction()
{
    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){
        --mIndex;
    }
    else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){
        ++mIndex;
    }
    mIndex = Clamp( 0, mIndex, BattleAction_Num - 1 );
    
    if( KeyInput()->IsTrig( InputKey::Type_Enter ) ) 
    {
        //選択した時の処理
    }
}

void StateBattle::UpdateProcAction()
{
}

void StateBattle::UpdateDrawAction()
{
}

void StateBattle::UpdateTurnEnd()
{
}

void StateBattle::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "戦闘画面");
    
    DrawFormatString( 0 , 50+mIndex*15 , GetColor(0,255,0) , "→");

    char const* action_name[] =
    {
        "攻撃",
        "祈る",
        "逃げる",
    };
    for( int i = 0; i < BattleAction_Num ; i++ ){
        DrawFormatString( 20 , 50+i*15 , GetColor(0,255,0) , action_name[i]);
    }

    DrawFormatString( 120 , 50 ,    GetColor(0,255,0) , "Enemy:hp[%d],attack[%d]",gEnemyParam.mHp,gEnemyParam.mAttack);
    
    mEnemyAvater->Draw(200,200);
}

