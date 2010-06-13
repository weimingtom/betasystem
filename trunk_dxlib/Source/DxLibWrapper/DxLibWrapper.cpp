#include "DxLibWrapper.hpp"

#include <memory>
#include "System/StateBase.hpp"
#include "System/Vector2.hpp"
#include "Project/StateGameMain.hpp"

std::auto_ptr< StateBase > g_state;

int InitApplication()
{
    SetGraphMode( 640 , 480 , 16 ) ;
    ChangeWindowMode( TRUE ) ;
    if( DxLib_Init() == ApplicationFailure ) { return ApplicationFailure; }
    
    SetDrawScreen( DX_SCREEN_BACK );

    g_state.reset( new_StateGameMain() );

    return ApplicationSuccess;
}

void LoopApplication()
{
    while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
    {
        g_state->Update();
        
        ClearDrawScreen() ;    // ��ʂ�����������
        
        g_state->Draw();

        ScreenFlip() ;    // ����ʂ̓��e��\��ʂɔ��f������
    }
}

int EndApplication()
{
    DxLib_End();
    return ApplicationSuccess;
}


/**
    ���ߐF�𖳌��ɂ���@��Ȃ��̂ŁA
    ���b�v���Ĉ��������炷.
*/
void DrawGraph( int x , int y , int image_handle )
{
    DrawGraph( x , y , image_handle , TRUE );
}

/**
    Vector2 �ł̉摜�`��.
*/
void DrawGraph( Vector2 pos , int image_handle )
{
    DrawGraph( pos.x , pos.y , image_handle );
}
