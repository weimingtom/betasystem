#include "System/AnimFormat.hpp"

/**
	プロジェクトで使用する、全てのアニメーションデータ(直打ち).
*/
AnimFormat const gAnimData[ AnimType_Num ] =
{
	{ 2, 0, 0, 100, 100, 5, -1 }
	{ 2, 0, 0, 100, 100, 5, -1 }
};

AnimFormat const& AnimDataOf( AnimType anim_type )
{
	return gAnimData[anim_type];
}


