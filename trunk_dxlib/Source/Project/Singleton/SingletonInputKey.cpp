#include "SingletonInputKey.hpp"

#include <memory>

std::auto_ptr<InputKey> gInputKey;

namespace Singleton
{
    void InitKeyInput()
    {
        gInputKey.reset( new_InputKey() );
    }
    void UpdateKeyInput()
    {
        gInputKey->Update();
    }
} // namespace Singleton

InputKey* KeyInput()
{
    return gInputKey.get();
}

