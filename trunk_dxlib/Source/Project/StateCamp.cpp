#include "Project/StateCamp.hpp"

#include <memory>
#include "System/StateBase.hpp"
#include "System/StateManagerBase.hpp"
#include "DxLibWrapper/MouseInput.hpp"
#include "DxLibWrapper/ImageLoader.hpp"
#include "DxLibWrapper/Graphics.hpp"
#include "Project/ProjectImageLoader.hpp"
#include "Project/ProjectStateManager.hpp"
#include "Project/CharacterStatus.hpp"
#include "Project/CharacterStatusFactory.hpp"
#include "Project/SaveData.hpp"

class StateCamp : public StateBase
{
public:
    StateCamp( StateManagerBase& project_state_manager );
public:
    void Update();
    void Draw();
private:
    StateManagerBase& m_project_state_manager;
    std::auto_ptr< ImageLoader > m_image_loader;
    std::auto_ptr< MouseInput > m_mouse_input;
};

StateCamp::StateCamp( StateManagerBase& project_state_manager )
 : m_project_state_manager( project_state_manager )
 , m_image_loader( new_ImageLoader() )
 , m_mouse_input( new_MouseInput() )
{
    m_image_loader->Load();
    CharacterStatus& player_status = SaveData::GetInstance().m_player_status;
    player_status.m_hp = player_status.m_hp_max;
}

void StateCamp::Update()
{
    m_mouse_input->Update();
    if( m_mouse_input->IsTrig( MouseInput::Type_Left ) )
    {
        m_project_state_manager.ChangeState( ProjectState_WorldMap );
    }
}

void StateCamp::Draw()
{
    DrawGraph( 0 , 0 , m_image_loader->ImageHandleOf( NameOf( ImageType_Camp ) ) );
}

StateBase* new_StateCamp( StateManagerBase& project_state_manager )
{
    return new StateCamp( project_state_manager );
}

