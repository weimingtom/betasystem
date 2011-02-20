#include "AnimData.hpp"

#include "System/AnimFormat.hpp"

/**
	プロジェクトで使用する、全てのアニメーションデータ(直打ち).
*/
AnimFormat const gAnimData[ AnimType_Num ] =
{
    //  枚数,   x,  y,  width,  height, 表示期間,   ループ回数
	{   2,      0,  0,  100,    150,    30,         AnimFormat::InfinityLoop },
};

AnimFormat const& AnimDataOf( AnimType anim_type )
{
	return gAnimData[anim_type];
}

