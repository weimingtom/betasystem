#include "StateLuaTest.hpp"

#include <assert.h>
#include <lua.hpp>
#include "DxLibWrapper/Color.hpp"

namespace Princess {

StateLuaTest::StateLuaTest()
{
    mLuaState = luaL_newstate();

    if( luaL_loadfile( mLuaState, "Resource/Lua/sample.lua" ) || lua_pcall(mLuaState, 0, 0, 0) ) {
        assert( !"sample.luaを開けませんでした" );
    }
}

StateLuaTest::~StateLuaTest()
{
    lua_close(mLuaState);
}

void StateLuaTest::Update()
{
    // グローバル変数を読む
    lua_getglobal( mLuaState, "Name" );
    if( lua_isstring( mLuaState, -1 ) ){
        DrawFormatString( 0 , 20 , ColorOf(0,255,0) , "変数Name=[%s] \n", lua_tostring(mLuaState, -1) );
    }
    lua_pop(mLuaState,1);
}

void StateLuaTest::Draw()
{
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "lua検証画面");
}


} // namespace Princess

