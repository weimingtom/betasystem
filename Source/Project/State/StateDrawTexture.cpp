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
	DrawGraph(0,0, Princess::ImageLoader::GetInstance()->ImageHandleOf( static_cast<Princess::ImageType>(mIndex) ), FALSE );

    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "画像表示テストシーケンス" );
    DrawFormatString( 0 , 20 , ColorOf(0,255,0) , "上下キーで、表示可能な状態にある画像を切り替えて表示します" );
    
    if( KeyInput()->IsTrig( InputKey::Type_Up ) ){
        mIndex--;
    }else if( KeyInput()->IsTrig( InputKey::Type_Down ) ){
        mIndex++;
    }
    mIndex = Clamp( 0, mIndex, Princess::ImageType_Num - 1 );

	DrawFormatString( 0+1 , 40+1 , ColorOf(0,0,0) , "%s", Princess::ImageLoader::NameOf( static_cast<Princess::ImageType>(mIndex) ) );
    DrawFormatString( 0 , 40 , ColorOf(230,230,230) , "%s", Princess::ImageLoader::NameOf( static_cast<Princess::ImageType>(mIndex) ) );
}

void StateDrawTexture::Draw()
{
}

