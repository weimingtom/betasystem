#ifndef STATE_PALETTE_TEST_HPP__
#define STATE_PALETTE_TEST_HPP__

#include "System/StateBase.hpp"

class StatePaletteTest : public StateBase
{
public:
    StatePaletteTest();
    ~StatePaletteTest();
public:
	void Update();
	void Draw() const;
private:
    int const mSoftImageHandle;
    int mChangedColorImageHandle;
};

#endif // STATE_PALETTE_TEST_HPP__
