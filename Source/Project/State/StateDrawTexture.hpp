#ifndef STATE_DRAW_TEXTURE_HPP_
#define STATE_DRAW_TEXTURE_HPP_

#include "System/StateBase.hpp"

/**
   画像描画テスト.
*/
class StateDrawTexture : public StateBase
{
public:
    StateDrawTexture();
    ~StateDrawTexture();
public:
	void Update();
	void Draw();
private:
    int mIndex;
};

#endif // STATE_DRAW_TEXTURE_HPP_

