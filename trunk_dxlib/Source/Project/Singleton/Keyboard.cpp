#include "Keyboard.hpp"

#include <memory>

std::auto_ptr<KeyboardInput> gKeyInput;

namespace Singleton
{
    void InitKeyInput()
    {
        gKeyInput.reset( new_KeyboardInput() );
    }
    void UpdateKeyInput()
    {
        gKeyInput->Update();
    }
} // namespace Singleton

KeyboardInput* KeyInput()
{
    return gKeyInput.get();
}

