#include "StateCharacterGenerate.hpp"

#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"

StateCharacterGenerate::StateCharacterGenerate()
 : m_step( Step_Title )
 , m_frame(0)
{
}

void StateCharacterGenerate::Update()
{
}

void StateCharacterGenerate::Draw()
{
    switch( m_step )
    {
    case Step_Title:
        DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "キャラ生成テスト");
        break;
    }
}

