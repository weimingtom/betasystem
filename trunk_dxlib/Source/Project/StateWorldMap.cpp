#include "Project/StateWorldMap.hpp"
#include <memory>
#include "System/StateBase.hpp"
#include "System/StateManagerBase.hpp"
#include "DxLibWrapper/MouseInput.hpp"
#include "DxLibWrapper/Graphics.hpp"
#include "DxLibWrapper/Color.hpp"
#include "DxLibWrapper/ImageLoader.hpp"
#include "Project/ProjectStateManager.hpp"

class StateWorldMap : public StateBase
{
public:
    StateWorldMap( StateManagerBase& project_state_manager );
    
public:
    void Update();
    void Draw();
    
private:
    std::auto_ptr< MouseInput > m_mouse;
    StateManagerBase& m_project_state_manager;
    std::auto_ptr< ImageLoader > m_image_loader;
    
private:
    enum ImageType
    {
        ImageType_WorldMap,
        ImageType_Num,
    };
    static char const* const m_image_list[ ImageType_Num ];
};

char const* const StateWorldMap::m_image_list[ ImageType_Num ] =
{
    "Resource/WorldMap.png",
};

StateWorldMap::StateWorldMap( StateManagerBase& project_state_manager )
 : m_mouse( new_MouseInput() )
 , m_project_state_manager( project_state_manager )
 , m_image_loader( new_ImageLoader( m_image_list , ImageType_Num ) )
{
    m_image_loader->Load();
}

void StateWorldMap::Update()
{
    m_mouse->Update();
    if( m_mouse->IsTrig( MouseInput::Type_Left ) )
    {
        m_project_state_manager.ChangeState( ProjectState_Battle );
    }
}

void StateWorldMap::Draw()
{
    DrawGraph( 0 , 0 , m_image_loader->ImageHandleOf( m_image_list[ ImageType_WorldMap ] ) );
    DrawFormatString( 0,0, ColorOf(255,255,255) , "ワールドマップ");
}

StateBase* new_StateWorldMap( StateManagerBase& project_state_manager )
{
    return new StateWorldMap( project_state_manager );
}

