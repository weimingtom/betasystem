#ifndef CharacterDrawer_hpp
#define CharacterDrawer_hpp

class CharacterDrawer
{
public:
    CharacterDrawer();
    ~CharacterDrawer();
public:
    enum CharaType{
        CharaType_None,
        CharaType_Furiru,
        CharaType_Slime,
    };
    enum CharaPos{
        CharaPos_Left,
        CharaPos_Right,
    };
public:
    void SetChara(CharaType,CharaPos);
    void Update();
    void Draw()const;
};

#endif

