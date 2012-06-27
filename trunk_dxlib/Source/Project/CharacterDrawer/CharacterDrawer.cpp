#include "CharacterDrawer.hpp"
#include "DxLibWrapper/Color.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "Project/Draw.hpp"


CharacterDrawer::CharacterDrawer()
{
}

CharacterDrawer::~CharacterDrawer()
{
}

void CharacterDrawer::Update()
{
}

void CharacterDrawer::Draw() const
{
    DrawFormatString( 0 , 300 , ColorOf(0,255,0) , "CharacterDrawer is Running..." );
    
    //ƒLƒƒƒ‰‚Ì—§‚¿ˆÊ’u.
    Vector2 chara_pos[CharaPos_Num];
    chara_pos[CharaPos_Left].x = 0; 
    chara_pos[CharaPos_Left].x = 0; 
    chara_pos[CharaPos_Right].x = 320;
    chara_pos[CharaPos_Right].y = 0;
    
    for( int i = 0 ; i < CharaPos_Num ; i ++ ){
        if( m_draw_info[i].image_type != ImageType_Dummy ){
            DrawTexture( chara_pos[i], m_draw_info[i].image_type );
        }
    }
}

void CharacterDrawer::SetChara(ImageType type, CharaPos pos)
{
    m_draw_info[pos].image_type = type;
}

