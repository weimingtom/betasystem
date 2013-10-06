﻿#include "KoyakuType.h"

char const* NameOf(KoyakuType koyaku_type)
{
	static char const* name_table[kKoyakuType_Num] =
	{
		"はずれ",
		"リプレイ",
		"ベル",
		"弱チェリー",
		"スイカ",
		"弱チャンス目",
		"強チェリー",
		"中段チェリー",
	};
	return name_table[koyaku_type];
}
