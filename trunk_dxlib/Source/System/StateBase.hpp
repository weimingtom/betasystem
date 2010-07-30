#ifndef include_c82b7371_13fb_4be4_932a_c46b78725873
#define include_c82b7371_13fb_4be4_932a_c46b78725873

/**
    ‘JˆÚŠî–{ƒNƒ‰ƒX.
*/
class StateBase
{
public:
    virtual ~StateBase(){}
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

#endif
