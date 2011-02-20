#ifndef keyboardinput_hpp
#define keyboardinput_hpp

/**
    キーボード入力管理.
*/
class KeyboardInput
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
        Type_RightControl,
        Type_0,
        Type_1,
        Type_2,
        Type_3,
        Type_4,
        Type_5,
        Type_6,
        Type_7,
        Type_8,
        Type_9,
        
        Type_Num,
    };
    
public:
    friend KeyboardInput* new_KeyboardInput();
    virtual ~KeyboardInput(){}
    
public:
    virtual void Update() = 0;
    virtual bool IsTrig( Type type ) const = 0;
    virtual bool IsHold( Type type ) const = 0;
private:
    class Impl;
};

KeyboardInput* new_KeyboardInput();

#endif // keyboardinput_hpp
