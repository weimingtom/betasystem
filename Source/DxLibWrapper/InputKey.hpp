#ifndef InputKey_hpp
#define InputKey_hpp

/**
    キーボード入力管理.
*/
class InputKey
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
        Type_LeftControl,
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
        Type_F1,
        Type_F2,
        Type_F3,
        Type_F4,
        Type_F5,
        Type_F6,
        Type_F7,
        Type_F8,
        Type_F9,
        Type_F10,
        Type_F11,
        Type_F12,
        Type_A,
        Type_B,
        Type_C,
        Type_D,
        Type_E,
        Type_F,
        Type_G,
        Type_H,
        Type_I,
        Type_J,
        Type_K,
        Type_L,
        Type_M,
        Type_N,
        Type_O,
        Type_P,
        Type_Q,
        Type_R,
        Type_S,
        Type_T,
        Type_U,
        Type_V,
        Type_W,
        Type_X,
        Type_Y,
        Type_Z,
        Type_Num,
    };
    
public:
    friend InputKey* new_InputKey();
    virtual ~InputKey(){}
    
public:
    virtual void Update() = 0;
    virtual bool IsTrig( Type type ) const = 0;
    virtual bool IsHold( Type type ) const = 0;
    virtual bool IsRelease( Type type ) const = 0;
    virtual int GetHoldFrame( Type type ) const = 0;
private:
    class Impl;
};

InputKey* new_InputKey();

#endif // InputKey_hpp
