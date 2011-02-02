#include <DxLib.h>
/*
	マウス入力関連.
*/
class Vector2;

class InputMouse
{
public:
	enum Type
	{
		Type_Right,
		Type_Left,
		Type_Middle,
		Type_Num,
	};
    
public:
    friend InputMouse* new_InputMouse( int is_visible_cursor );
    virtual ~InputMouse(){}

public:
    virtual void Update() = 0;

public:
    virtual Vector2 Position() const = 0;
    virtual void SetPos( int x , int y ) const = 0;
    virtual bool IsTrig( Type type ) const = 0;
    virtual bool IsHold( Type type ) const = 0;

private:
	class Impl;
};


InputMouse* new_InputMouse( int is_visible_cursor = TRUE );

