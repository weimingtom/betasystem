#ifndef avaterparam_hpp
#define avaterparam_hpp

//オプション
enum TypeOption
{
	Option_None,
	Option_Grass,
	Option_Slime,
	
	Option_Num,
};

//服の種類
enum TypeCloth
{
	Cloth_Sailer,
	Cloth_Maido,
	Cloth_Parker,
	Cloth_T,
	
	Cloth_Num,
};

//顔の種類
enum TypeFace
{
	Face_Tare,
	Face_Jito,
	Face_Tsuri,
	Face_Aho,

	Face_Num,
};

//髪の色
enum TypeHairColor
{
	HairColor_Black,
	HairColor_Red,
	HairColor_Green,
	HairColor_Blue,
	
	HairColor_Num,
};

//髪型
enum TypeHair
{
	Hair_Long,
	Hair_Short,
	Hair_Twin,
	Hair_Pony,

	Hair_Num,
};

//容姿まとめ
struct AvaterParam
{
	TypeCloth cloth;
	TypeFace face;
	TypeHair hair;
	TypeHairColor haircolor;
	AvaterParam()
	{
		cloth = Cloth_Sailer;
		face = Face_Tare;
		hair = Hair_Long;
		haircolor = HairColor_Black;
	}
};

#endif

