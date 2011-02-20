#ifndef keyboard_hpp
#define keyboard_hpp
/** @file
    �v���W�F�N�g�B��̃L�[���͊Ǘ�.
*/
#include "DxLibWrapper/KeyboardInput.hpp"

namespace Singleton
{
    /**
        �L�[���͏�����.
    */
    void InitKeyInput();
    /**
        �L�[���͍X�V.
    */
    void UpdateKeyInput();
}// namespace

/**
    �C���X�^���X�̎擾.
*/
KeyboardInput* KeyInput();

#endif
