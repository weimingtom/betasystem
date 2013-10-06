#ifndef PP_PLAYER_STATUS_H_
#define PP_PLAYER_STATUS_H_

#include "DrawingStatus.h"

//! プレイヤー状態.
struct PlayerStatus
{
	int coin;						//!< 所持コイン.
	DrawingStatus drawing_status;	//!< 抽選状態.

	PlayerStatus()
	{
		coin = 500;
		drawing_status = kDrawingStatus_Normal;
	}
};

#endif // PP_PLAYER_STATUS_H_
