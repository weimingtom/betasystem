#include "StateTitle.hpp"

#include "Project/Draw.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "System/StateManagerBase.hpp"
#include "Project/ProjectStateManager.hpp"

StateTitle::StateTitle( StateManagerBase* manager )
 : m_manager( manager )
{
}

void StateTitle::Update()
{
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
        m_manager->ChangeState( ProjectState_Battle );
    }
}

void StateTitle::Draw()
{
	DrawTexture( 0, 0, ImageType_Stand );
}


