#ifndef PP_KOYAKU_TYPE_H_
#define PP_KOYAKU_TYPE_H_

//! 子役の種類.
enum KoyakuType
{
	kKoyakuType_Hazure,			//!<はずれ.
	kKoyakuType_Replay,         //!<リプレイ.
	kKoyakuType_Bell,           //!<ベル.
	kKoyakuType_WeakCherry,     //!<弱チェリー.
	kKoyakuType_WaterMelon,     //!<スイカ.
	kKoyakuType_WeakChance,     //!<弱チャンス目.
	kKoyakuType_StrongCherry,   //!<強チェリー.
	kKoyakuType_StrongChance,   //!<強チャンス目.
	kKoyakuType_BonusCherry,    //!<確定チェリー.
	kKoyakuType_Num,
};

char const* NameOf(KoyakuType koyaku_type);

#endif //PP_KOYAKU_TYPE_H_

