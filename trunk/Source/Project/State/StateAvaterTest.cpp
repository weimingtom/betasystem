#include "StateAvaterTest.hpp"

StateAvaterTest::StateAvaterTest()
{
}

StateAvaterTest::~StateAvaterTest()
{
}

void StateAvaterTest::Update()
{
}

void StateAvaterTest::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "アバター描画テスト");
}

