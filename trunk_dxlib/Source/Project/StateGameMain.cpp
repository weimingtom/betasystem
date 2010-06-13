#include "System/StateBase.hpp"

#include <assert.h>
#include <memory>
#include "DxLibWrapper/DxLibWrapper.hpp"
#include "DxLibWrapper/ImageLoader.hpp"
#include "DxLibWrapper/MouseInput.hpp"
#include "Project/Character.hpp"
#include "System/ArraySize.hpp"
#include "System/Vector2.hpp"
#include "System/CheckHit.hpp"


enum ImageType
{
    ImageType_Forest,
    ImageType_Player,
    ImageType_Num,
};

char const* const image_name[ ImageType_Num ] =
{
    "Resource/Image.png",
    "Resource/Player.png",
};

class StateGameMain : public StateBase
{
public:
    StateGameMain();
    
public:
    void Update();
    void Draw();
    
private:
    void DrawCharacterStatus( Character chara , int base_x , int base_y );
    
private:
    std::auto_ptr< ImageLoader > m_image_loader;
    std::auto_ptr< MouseInput > m_mouse;
    Character m_player;
    Character m_enemy;
};

StateGameMain::StateGameMain()
 : m_image_loader( new_ImageLoader( image_name , ARRAY_SIZE(image_name) ) )
 , m_mouse( new_MouseInput() )
{
    m_image_loader->Load();
}

void StateGameMain::Update()
{
    m_mouse->Update();
}

void StateGameMain::Draw()
{
    //”wŒi•`‰æ
    DrawGraph( 0 , 0 , m_image_loader->ImageHandleOf( image_name[ ImageType_Forest ] ) , TRUE );
    //ƒLƒƒƒ‰•`‰æ
    {
        Vector2 pos( 400 , 250 );
        DrawGraph( pos , m_image_loader->ImageHandleOf( image_name[ ImageType_Player ] ) );
    }
    
    DrawFormatString( 0 , 0 , DefaultFontColor() , "GameMainState." );
    
    //‹éŒ`•`‰æ
    {
        Vector2 pos( 10, 20 );
        Vector2 size( 200 , 100 );
        DrawBox( pos.x , pos.y , (pos+size).x , (pos+size).y , DefaultFontColor() ,TRUE );
        DrawFormatString( 100 , 0 , DefaultFontColor() , "CheckHit[%d]" , CheckHit( m_mouse->Position() , pos , size ) );
    }
    
    DrawCharacterStatus( m_player , 10 , 50 );
    DrawCharacterStatus( m_enemy , 300 , 50 );
}

void StateGameMain::DrawCharacterStatus( Character chara , int base_x , int base_y )
{
    int y = base_y;
    int const margin_y = 20;
    DrawFormatString( base_x , y += margin_y , DefaultFontColor() ,
        "hp:[%d]/[%d]" , chara.m_hp , chara.m_hp_max );
    DrawFormatString( base_x , y += margin_y , DefaultFontColor() ,
        "action:[%d],[%d],[%d]" , chara.m_action[0] , chara.m_action[1] , chara.m_action[2] );
    DrawFormatString( base_x , y += margin_y , DefaultFontColor() ,
        "action_next:[%d]" , chara.m_action_next );
}

StateBase* new_StateGameMain()
{
    return new StateGameMain();
}

