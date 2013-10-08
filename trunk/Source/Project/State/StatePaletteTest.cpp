#include "StatePaletteTest.hpp"

#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "System/StateManagerBase.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"

StatePaletteTest::StatePaletteTest()
{
}

StatePaletteTest::~StatePaletteTest()
{
}

void StatePaletteTest::Update()
{
}

void StatePaletteTest::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "パレットテスト");
}

