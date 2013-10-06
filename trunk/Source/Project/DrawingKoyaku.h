#ifndef PP_DRAWING_KOYAKU_H_
#define PP_DRAWING_KOYAKU_H_

#include "KoyakuType.h"
#include "KoyakuParameter.h"
#include "DrawingStatus.h"

//! 抽選結果.
struct DrawingResult{
	KoyakuType koyaku_type;		//!< どの子役を引いたか.
	bool is_art;				//!< artに当選しているか.
	bool is_koukaku;			//!< 高確率抽選に当選したか.
	bool is_teikaku;			//!< 低確率抽選に当選したか.
	
	//! コンストラクタ.
	DrawingResult()
	{
		koyaku_type = kKoyakuType_Hazure;
		is_art = false;
		is_koukaku = false;
		is_teikaku = false;
	}
};

//! 抽選処理.
DrawingResult GetDrawingResult(DrawingStatus drawing_status);

//! 子役のコイン枚数.
int CoinOf(KoyakuType koyaku_type);

#endif //PP_DRAWING_KOYAKU_H_