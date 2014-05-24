#include "StateLuaTest.hpp"

#include "DxLibWrapper/Color.hpp"

namespace Princess {

StateLuaTest::StateLuaTest()
{
}

void StateLuaTest::Update()
{
}

void StateLuaTest::Draw() const
{
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "lua検証画面");
}


} // namespace Princess

