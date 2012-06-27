#ifndef CharacterDrawer_hpp
#define CharacterDrawer_hpp

#include "Project/Singleton/SingletonImageLoader.hpp"

class CharacterDrawer
{
public:
    CharacterDrawer();
    ~CharacterDrawer();
public:
    enum CharaPos{
        CharaPos_Left,
        CharaPos_Right,
        CharaPos_Num,
    };
public:
    struct DrawInfo{
        ImageType image_type;
        DrawInfo()
        {
            image_type = ImageType_Dummy;
        }
    };
public:
    void SetChara(ImageType,CharaPos);
    void Update();
    void Draw()const;
private:
    DrawInfo m_draw_info[CharaPos_Num];
};

#endif

