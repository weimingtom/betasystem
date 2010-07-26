#include "Project/StateWorldMap.hpp"
#include <memory>
#include "System/StateBase.hpp"
#include "System/StateManagerBase.hpp"
#include "DxLibWrapper/MouseInput.hpp"
#include "DxLibWrapper/Color.hpp"
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
};

StateWorldMap::StateWorldMap( StateManagerBase& project_state_manager )
 : m_mouse( new_MouseInput() )
 , m_project_state_manager( project_state_manager )
{
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
    DrawFormatString( 0,0, ColorOf(255,255,255) , "ワールドマップ");
}

StateBase* new_StateWorldMap( StateManagerBase& project_state_manager )
{
    return new StateWorldMap( project_state_manager );
}

