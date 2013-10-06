#ifndef PP_DRAWING_STATUS_H_
#define PP_DRAWING_STATUS_H_

//! 抽選状態
enum DrawingStatus
{
	kDrawingStatus_Normal,	//!< 通常.
	kDrawingStatus_Koukaku,	//!< 高確.
	kDrawingStatus_Tyoukou,	//!< 超高確.
	kDrawingStatus_Num,		//!< 総数.
};

#endif // PP_DRAWING_STATUS_H_

