#include "StateTitle.hpp"

#include "Project/Draw.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "Project/SaveData.hpp"

StateTitle::StateTitle()
 : m_step( Step_Title )
 , m_frame(0)
{
    gSaveData.Save();
}

void StateTitle::Update()
{
}

void StateTitle::Draw() const
{
    switch( m_step )
    {
    case Step_Title:
        DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "ƒ^ƒCƒgƒ‹‰æ–Ê");
        break;
    }
}

