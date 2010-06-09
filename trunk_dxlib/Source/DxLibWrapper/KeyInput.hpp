/*
	ƒL[“ü—ÍŠÖ˜A.
*/
class KeyInput
{
public:
	enum Type
	{
		Type_Up,
		Type_Down,
		Type_Left,
		Type_Right,
		Type_Enter,
		Type_Backspace,
		Type_RightShift,
		Type_RightControl,
		Type_Num,
	};
public:
	virtual ~KeyInput(){}

public:
	virtual void Update() = 0;

public:
	virtual bool IsTrig( Type ) = 0;
	virtual bool IsHold( Type ) = 0;

};