#include "AvaterParam.hpp"

char const* NameOf(TypeOption type)
{
	static char const* name[Option_Num] =
	{
		"なし",
		"眼鏡",
		"スライムぬいぐるみ",
	};
	return name[type];
}
char const* NameOf(TypeCloth type)
{
	static char const* name[Cloth_Num] =
	{
		"セーラー服",
		"メイド服",
		"パーカー",
		"Ｔシャツ",
	};
	return name[type];
}
char const* NameOf(TypeFace type)
{
	static char const* name[Face_Num] =
	{
		"垂れ目",
		"ジト目",
		"釣り目",
		"アホ目",
	};
	return name[type];
}
char const* NameOf(TypeHairColor type)
{
	static char const* name[HairColor_Num] =
	{
		"黒",
		"赤",
		"緑",
		"青",
		"黄色",
	};
	return name[type];
}
char const* NameOf(TypeHair type)
{
	static char const* name[Hair_Num] =
	{
		"ロング",
		"ショート",
		"ツインテール",
		"ポニーテール",
	};
	return name[type];
}

