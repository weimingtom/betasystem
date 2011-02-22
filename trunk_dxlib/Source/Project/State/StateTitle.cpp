#include "StateTitle.hpp"

#include "Project/Draw.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/State/ProjectStateManager.hpp"

StateTitle::StateTitle( StateManagerBase* manager )
 : m_manager( manager )
 , m_step( Step_Title )
 , m_frame(0)
{
}

void StateTitle::Update()
{
    switch( m_step )
    {
    case Step_Title:
        m_frame++;
        if( m_frame > 300 ){ m_step = Step_TitleMovie; }
        if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
        {
            m_manager->ChangeState( ProjectState_Battle );
        }
        break;
    case Step_TitleMovie:
        m_frame++;
        if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
        {
            m_step = Step_Title;
            m_frame = 0;
        }
        break;
    }
}

void StateTitle::Draw() const
{
    switch( m_step )
    {
    case Step_Title:
        DrawTexture( Vector2(0,0), ImageType_Title );
        break;
    case Step_TitleMovie:
        {
            char const* message[] =
            {
                "���̂ނ����A���̉ʂĂɏ����ȍ���������",
                "�����́A�������Ȃ�����L���ɔɉh���Ă����B",
                "������������A���̍��ɂ��錕��~������卑���U�߂Ă��܂����B",
                "���̐��A���悻�P���B",
                "�����̕P�͈�l�A���̐킢�ւƌ������܂����B",
            };
            for( int i=0 ; i<ARRAY_SIZE(message) ; i++ ){
                DrawFormatString( 0 , 480 - m_frame/2 + i*15 , ColorOf(255,255,255) , "%s", message[i] );
            }
        }
        break;
    }
}

