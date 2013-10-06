#include "DrawingKoyaku.h"
#include <stdlib.h>
#include <iostream>
#include "KoyakuType.h"
#include "KoyakuParameter.h"
#include "DrawingStatus.h"


namespace {

//! 乱数分母
static int const kRandomMax = 65535;

//! 子役を引く確率.
int sKoyakuPercent[kKoyakuType_Num] = 
{
	kRandomMax,		//!<はずれ.
	kRandomMax/7,	//!<リプレイ.
	kRandomMax/36,	//!<ベル.
	kRandomMax/99,	//!<弱チェリー.
	kRandomMax/99,	//!<スイカ.
	kRandomMax/194,	//!<弱チャンス目.
	kRandomMax/260,  //!<強チェリー.
	kRandomMax/178,  //!<強チャンス目.
	kRandomMax/1820,	//!<確定チェリー.
};

//! 子役の当選確率.
KoyakuParameter sKoyakuTable[kKoyakuType_Num][kDrawingStatus_Num] = 
{
	//ART率,高確率,超高率
	// ハズレ
	{
		{0,0,0},
		{0,0,0},
		{0,0,0},
	},
	// リプレイ.
	{
		{0,0,0},
		{0,0,0},
		{0,0,0},
	},
	// ベル
	{
		{0,0,0},
		{0,0,0},
		{0,0,0},
	},
	// 弱チェリー
	{
		{kRandomMax/50,0,0},
		{0,0,0},
		{0,0,0},
	},
	// スイカ
	{
		{kRandomMax/50,0,0},
		{0,0,0},
		{0,0,0},
	},
	// 弱チャンス目
	{
		{kRandomMax/10,0,0},
		{0,0,0},
		{0,0,0},
	},
	// 強チェリー
	{
		{kRandomMax/3,0,0},
		{0,0,0},
		{0,0,0},
	},
	// 強チャンス目.
	{
		{kRandomMax/3,0,0},
		{0,0,0},
		{0,0,0},
	},
	// 確定チェリー.
	{
		{kRandomMax,0,0},
		{0,0,0},
		{0,0,0},
	},
};

bool Drawing(int percent)
{
	int const rand_num = rand() % kRandomMax;
	std::cout << percent << "未満ならok:" << rand_num << "\n";
	return ( rand_num < percent );
}

} // namespace unnamed

DrawingResult GetDrawingResult(DrawingStatus drawing_status)
{
	DrawingResult result;
	//子役抽選.
	std::cout << "子役抽選\n";
	for( int i = kKoyakuType_Num-1 ; i >= 0 ; i-- ){
		if( Drawing( sKoyakuPercent[i] ) ){
			result.koyaku_type = static_cast<KoyakuType>(i);
			break;
		}
	}
	//ART抽選.
	std::cout << "ART抽選\n";
	KoyakuParameter const koyaku_param = sKoyakuTable[result.koyaku_type][drawing_status];
	result.is_art = Drawing( koyaku_param.art_percent );
	//@todo 高確率抽選.
	//@todo 低確率抽選.
	return result;
}

int CoinOf( KoyakuType koyaku_type )
{
	//! 子役のコイン枚数.
	static int const kKoyakuCoins[kKoyakuType_Num] = 
	{
		0,3,9,1,5,3,1,3,1,
	};
	return kKoyakuCoins[koyaku_type];
}

