#include "StateBattle.hpp"

#include "Project/Singleton/SaveData.hpp"
#include "Project/Singleton/PlayerParam.hpp"
#include "System/Range.hpp"
#include "System/ArraySize.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"

StateBattle::StateBattle()
 : mIndex(0)
{
}

StateBattle::~StateBattle()
{
}

void StateBattle::Update()
{
    enum BattleAction{
        BattleAction_Attack,
        BattleAction_Pray,
        BattleAction_Away,
        BattleAction_Num,
    };
    
    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){
        --mIndex;
    }
    else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){
        ++mIndex;
    }
    mIndex = Clamp( 0, mIndex, BattleAction_Num - 1 );
    
    if( KeyInput()->IsTrig( InputKey::Type_Enter ) ) 
    {
    }
}

void StateBattle::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "戦闘画面");
    
    DrawFormatString( 0 , 50+mIndex*15 , GetColor(0,255,0) , "→");
}

