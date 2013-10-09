#include "StateGameMain.hpp"

StateGameMain::StateGameMain()
{
}

void StateGameMain::Update()
{
}

void StateGameMain::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "ゲームメイン");
}
