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
                "そのむかし、東の果てに小さな国があった",
                "小国は、小さいながらも豊かに繁栄していた。",
                "しかしある日、聖剣を目当てに大国が攻めてきました。",
                "その数、およそ１万。",
                "小国の姫を筆頭に、兵士達は戦い抜きました。",
                "小国には精鋭が居ましたが、数の差は圧倒的で、",
                "次々と砦は破られていきました。",
                "とうとう敵は玉座まで迫り、",
                "その扉が今、破られようとしていました。",
            };
            for( int i=0 ; i<ARRAY_SIZE(message) ; i++ ){
                DrawFormatString( 0 , 480 - m_frame/2 + i*15 , ColorOf(255,255,255) , "%s", message[i] );
            }
        }
        break;
    }
}

