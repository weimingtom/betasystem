#ifndef STATE_LUA_TEST_HPP__
#define STATE_LUA_TEST_HPP__

#include "System/StateBase.hpp"

struct lua_State;

namespace Game{

/**
    lua検証用ステート.
*/
class StateLuaTest : public StateBase
{
public:
    StateLuaTest();
    ~StateLuaTest();
public:
	void Update();
	void Draw();
private:
    lua_State* mLuaState;
};

} // namespace Game

#endif // STATE_LUA_TEST_HPP__
