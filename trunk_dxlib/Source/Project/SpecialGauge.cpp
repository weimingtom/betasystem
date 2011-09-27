#include "SpecialGauge.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "Project/Draw.hpp"

void SpecialGauge::Draw() const
{
    int x = 0;
    int y = 120;
    DrawTexture( Vector2(x,y) , ImageType_SwordFrame );
    int const sword_of_hand = 40;
    int width = 150;
    DrawRectGraph(
        x,y,
        0,0,
        40 + (width - sword_of_hand)/ GaugeMax * mGaugeNum,
        75,
        ImageHandleOf(ImageType_SwordPower), TRUE, FALSE );
}

