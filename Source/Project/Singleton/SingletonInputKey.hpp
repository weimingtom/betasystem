#ifndef keyboard_hpp
#define keyboard_hpp
/** @file
    プロジェクト唯一のキー入力管理.
*/
#include "DxLibWrapper/InputKey.hpp"

namespace Singleton
{
    /**
        キー入力初期化.
    */
    void InitKeyInput();
    /**
        キー入力更新.
    */
    void UpdateKeyInput();
}// namespace

/**
    インスタンスの取得.
*/
InputKey* KeyInput();

#endif
