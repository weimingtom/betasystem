#include "CharacterDrawer.hpp"
#include "DxLibWrapper/Color.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "Project/Draw.hpp"
#include "System/Range.hpp"


CharacterDrawer::CharacterDrawer()
{
}

CharacterDrawer::~CharacterDrawer()
{
}

void CharacterDrawer::Update()
{
    for( int i = 0 ; i < CharaPos_Num ; i ++ ){
        m_draw_info[i].alpha+=15;
        m_draw_info[i].alpha = Clamp(0,m_draw_info[i].alpha,255);
	}
}

void CharacterDrawer::Draw() const
{
    //ƒLƒƒƒ‰‚Ì—§‚¿ˆÊ’u.
    Vector2 chara_pos[CharaPos_Num];
    chara_pos[CharaPos_Left].x = 0; 
    chara_pos[CharaPos_Left].x = 0; 
    chara_pos[CharaPos_Right].x = 320;
    chara_pos[CharaPos_Right].y = 0;
    
    for( int i = 0 ; i < CharaPos_Num ; i ++ ){
        if( m_draw_info[i].image_type != ImageType_Dummy ){
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_draw_info[i].alpha);
            DrawTexture( Vector2( chara_pos[i].x + ( -255 + m_draw_info[i].alpha ) / 4 , chara_pos[i].y ) , m_draw_info[i].image_type );
            SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
        }
    }

//    DrawFormatString( 0 , 300 , ColorOf(0,255,0) , "CharacterDrawer is Running..." );
}

void CharacterDrawer::SetChara(ImageType type, CharaPos pos)
{
    m_draw_info[pos].image_type = type;
    m_draw_info[pos].alpha = 0;
}

