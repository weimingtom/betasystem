#include "StateGameOver.hpp"

#include <memory>
#include "System/StateBase.hpp"
#include "System/StateManagerBase.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/ImageLoader.hpp"
#include "DxLibWrapper/Graphics.hpp"
#include "Project/ProjectStateManager.hpp"
#include "Project/CharacterStatus.hpp"
#include "Project/CharacterStatusFactory.hpp"
#include "Project/SaveData.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

class StateGameOver : public StateBase
{
public:
    StateGameOver( StateManagerBase& project_state_manager );
public:
    void Update();
    void Draw() const;
private:
    StateManagerBase& m_project_state_manager;
    std::auto_ptr< ImageLoader > m_image_loader;
};

StateGameOver::StateGameOver( StateManagerBase& project_state_manager )
 : m_project_state_manager( project_state_manager )
{
}

void StateGameOver::Update()
{
	InputMouse* m_mouse_input = SingletonInputMouse::Get();
    m_mouse_input->Update();
    if( m_mouse_input->IsTrig( InputMouse::Type_Left ) )
    {
//        m_project_state_manager.ChangeState( ProjectState_WorldMap );
    }
}

void StateGameOver::Draw() const
{
//	DrawTexture( 0 , 0 , SingletonImageLoader::Get()->ImageHandleOf( NameOf( ImageType_GameOver ) ) );
}

StateBase* new_StateGameOver( StateManagerBase& project_state_manager )
{
    return new StateGameOver( project_state_manager );
}

