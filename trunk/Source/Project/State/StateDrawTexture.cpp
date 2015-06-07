#include "StateDrawTexture.hpp"

#include "DxLibWrapper/Color.hpp"
#include "Project/Singleton/SingletonStateManager.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "System/Range.hpp"

StateDrawTexture::StateDrawTexture()
 : mIndex(0)
{
}

StateDrawTexture::~StateDrawTexture()
{
}

void StateDrawTexture::Update()
{
    DrawGraph(0,0, PrincessImageLoader::ImageHandleOf( static_cast<PrincessImageLoader::ImageType>(mIndex) ), FALSE );

    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "画像表示テストシーケンス" );
    DrawFormatString( 0 , 20 , ColorOf(0,255,0) , "上下キーで、表示可能な状態にある画像を切り替えて表示します" );
    
    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){
        mIndex--;
    }else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){
        mIndex++;
    }
    mIndex = Clamp( 0, mIndex, PrincessImageLoader::ImageType_Num - 1 );



    DrawFormatString( 0+1 , 40+1 , ColorOf(0,0,0) , "%s", PrincessImageLoader::NameOf( static_cast<PrincessImageLoader::ImageType>(mIndex) ) );
    DrawFormatString( 0 , 40 , ColorOf(230,230,230) , "%s", PrincessImageLoader::NameOf( static_cast<PrincessImageLoader::ImageType>(mIndex) ) );
}

void StateDrawTexture::Draw()
{
}

