#include "Project/StateWorldMap.hpp"

#include <memory>
#include <boost/foreach.hpp>
#include "System/StateBase.hpp"
#include "System/StateManagerBase.hpp"
#include "DxLibWrapper/MouseInput.hpp"
#include "DxLibWrapper/Graphics.hpp"
#include "DxLibWrapper/Color.hpp"
#include "DxLibWrapper/ImageLoader.hpp"
#include "DxLibWrapper/Button.hpp"
#include "Project/ProjectStateManager.hpp"
#include "Project/SaveData.hpp"
#include "Project/BackgroundFactory.hpp"

class StateWorldMap : public StateBase
{
public:
    StateWorldMap( StateManagerBase& project_state_manager );
    
public:
    void Update();
    void Draw();
    ButtonPtr new_ButtonCamp();
    ButtonPtr new_ButtonForest();
    ButtonPtr new_ButtonRedForest();
private:
    std::auto_ptr< MouseInput > m_mouse;
    StateManagerBase& m_project_state_manager;
    std::auto_ptr< ImageLoader > m_image_loader;
    ButtonPtrList m_button_list;
private:
    enum ImageType
    {
        ImageType_WorldMap,
        ImageType_StandFuriru,
        ImageType_Button_Camp,
        ImageType_Button_Forest,
        ImageType_Button_RedForest,
        ImageType_Num,
    };
    static char const* const m_image_list[ ImageType_Num ];
};

char const* const StateWorldMap::m_image_list[ ImageType_Num ] =
{
    "Resource/WorldMap.png",
    "Resource/Stand_Furiru.png",
    "Resource/button_camp.png",
    "Resource/button_forest.png",
    "Resource/button_red_forest.png",
};

StateWorldMap::StateWorldMap( StateManagerBase& project_state_manager )
 : m_mouse( new_MouseInput() )
 , m_project_state_manager( project_state_manager )
 , m_image_loader( new_ImageLoader( m_image_list , ImageType_Num ) )
{
    m_image_loader->Load();
    m_button_list.push_back( new_ButtonCamp() );
    m_button_list.push_back( new_ButtonForest() );
    m_button_list.push_back( new_ButtonRedForest() );
}

void StateWorldMap::Update()
{
    m_mouse->Update();
    Vector2 const mouse_pos = m_mouse->Position();
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        BOOST_FOREACH( ButtonPtr const& button , m_button_list )
        {
            if( button->CheckHit( mouse_pos ) )
            {
                if( button->Name() == "camp" )
                {
                    m_project_state_manager.ChangeState( ProjectState_Camp );
                }
                else if( button->Name() == "forest" )
                {
                    SetBackground( BackgroundType_Forest );
                    m_project_state_manager.ChangeState( ProjectState_Battle );
                }
                else if( button->Name() == "red_forest" )
                {
                    SetBackground( BackgroundType_RedForest );
                    m_project_state_manager.ChangeState( ProjectState_Battle );
                }
            }
        }
    }
}

void StateWorldMap::Draw()
{
    DrawGraph( 0 , 0 , m_image_loader->ImageHandleOf( m_image_list[ ImageType_WorldMap ] ) );
    DrawGraph( 300 , 0 , m_image_loader->ImageHandleOf( m_image_list[ ImageType_StandFuriru ] ) );
    DrawFormatString( 0,0, ColorOf() , "ワールドマップ");
    
    CharacterStatus const& player_status = SaveData::GetInstance().m_player_status;
    DrawFormatString( 0,20, ColorOf() , "hp[%d]/[%d]" , player_status.m_hp , player_status.m_hp_max );
    
    BOOST_FOREACH( ButtonPtr const& button , m_button_list )
    {
        button->Draw();
    }
}

ButtonPtr StateWorldMap::new_ButtonCamp()
{
    ButtonPtr result;
    Vector2 pos( 100 , 100 );
    Vector2 size( 100 , 100 );
    
    result.reset(
        new_Button(
            m_image_loader->ImageHandleOf( m_image_list[ImageType_Button_Camp] ),
            pos,
            size,
            0,
            "camp" )
    );
    return result;
}

ButtonPtr StateWorldMap::new_ButtonForest()
{
    ButtonPtr result;
    Vector2 pos( 200 , 200 );
    Vector2 size( 100 , 100 );
    
    result.reset(
        new_Button(
            m_image_loader->ImageHandleOf( m_image_list[ ImageType_Button_Forest ] ),
            pos,
            size,
            0,
            "forest" )
    );
    return result;
}

ButtonPtr StateWorldMap::new_ButtonRedForest()
{
    ButtonPtr result;
    Vector2 pos( 300 , 200 );
    Vector2 size( 100 , 100 );
    
    result.reset(
        new_Button(
            m_image_loader->ImageHandleOf( m_image_list[ ImageType_Button_RedForest ] ),
            pos,
            size,
            0,
            "red_forest" )
    );
    return result;
}


StateBase* new_StateWorldMap( StateManagerBase& project_state_manager )
{
    return new StateWorldMap( project_state_manager );
}

