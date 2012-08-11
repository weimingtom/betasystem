#include "StateTitle.hpp"

#include "Project/Draw.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "Project/SaveData.hpp"

StateTitle::StateTitle( StateManagerBase* manager )
 : m_manager( manager )
 , m_step( Step_Title )
 , m_frame(0)
{
    gSaveData.Save();
}

void StateTitle::Update()
{
    switch( m_step )
    {
    case Step_Title:
        if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
        {
            m_manager->ChangeState( ProjectState_Battle );
        }
/*
        else if( SingletonInputMouse::Get()->IsTrig(InputMouse::Type_Right) ){
            m_manager->ChangeState( ProjectState_TestMsg );
        }
*/
        break;
    }
}

void StateTitle::Draw() const
{
    switch( m_step )
    {
    case Step_Title:
        DrawTexture( Vector2(0,0), ImageType_Title );
//        DrawFormatString( 0 , 0 , ColorOf() , "総討伐数[%d]", gSaveData.m_total_break );
//        DrawFormatString( 0 , 20 , ColorOf() , "ハイスコア[%d]", gSaveData.m_max_break );
        break;
    }
}

