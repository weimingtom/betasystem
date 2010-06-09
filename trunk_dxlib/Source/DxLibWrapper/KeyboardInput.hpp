/**
    キーボード入力管理.
*/
class KeyBoardInput
{
public:
    enum Type
    {
        Type_Up,
        Type_Left,
        Type_Right,
        Type_Down,
        Type_Backspace,
        Type_Enter,
        Type_RightShift,
        Type_RightControll,
        
        Type_Num,
    };
public:
    virtual void Update() = 0;
    virtual bool IsTrig( Type type ) const = 0;
    virtual bool IsHold( Type type ) const = 0;
private:
    class Impl;
};
