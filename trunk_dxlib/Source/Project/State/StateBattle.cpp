#include "StateBattle.hpp"

#include "System/StateManagerBase.hpp"
#include "Project/ProjectStateManager.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Draw.hpp"

StateBattle::StateBattle( StateManagerBase& manager )
 : m_manager( manager )
{
}

void StateBattle::Update()
{
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
        m_manager.ChangeState( ProjectState_GameOver );
    }
}

void StateBattle::Draw()
{
	DrawTexture( 0, 0, ImageType_Forest );
}

