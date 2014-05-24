#ifndef STATE_LUA_TEST_HPP__
#define STATE_LUA_TEST_HPP__

#include "System/StateBase.hpp"

namespace Princess{

/**
    lua検証用ステート.
*/
class StateLuaTest : public StateBase
{
public:
    StateLuaTest();
    ~StateLuaTest(){}
public:
	void Update();
	void Draw() const;
};

} // namespace Princess

#endif // STATE_LUA_TEST_HPP__
