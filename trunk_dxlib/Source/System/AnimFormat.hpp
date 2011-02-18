#ifndef include_a570a0cd_752f_492d_8a1d_7b6a2916b806
#define include_a570a0cd_752f_492d_8a1d_7b6a2916b806

/**
	アニメーションフォーマット.
	@note 簡易すぎるが、プログラマが手打ち出来る様に
	最低限のフォーマットにしてみた.
*/
struct AnimFormat
{
	int anim_num;	//!< 総枚数.
	int begin_x;	//!< 切り取り開始位置 x.
	int begin_y;	//!< 切り取り開始位置 y.
	int width;		//!< 切り取り幅.
	int height;		//!< 切り取り高さ.
	int draw_frame;	//!< 1 枚を表示する長さ.
	int loop_num;	//!< ループ回数. -1 だと無限.
};

#endif // include_a570a0cd_752f_492d_8a1d_7b6a2916b806
