#include "StatePaletteTest.hpp"

#include "Project/Singleton/SingletonInputMouse.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "System/StateManagerBase.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

StatePaletteTest::StatePaletteTest()
 : mSoftImageHandle( ProjectImageLoader::SoftImageHandleOf( ProjectImageLoader::ImageType_Avater ) )
 , mChangedColorImageHandle(0)
{
    //パレット書き換え.
    SetPaletteSoftImage( mSoftImageHandle, 0, 255, 0, 0, 0 ) ;
    //イメージハンドル作成.
    mChangedColorImageHandle = CreateGraphFromSoftImage(mSoftImageHandle);
}

StatePaletteTest::~StatePaletteTest()
{
    DeleteGraph(mChangedColorImageHandle);
}

void StatePaletteTest::Update()
{
}

void StatePaletteTest::Draw() const
{
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "パレットテスト");
    DrawGraph(0,0,mChangedColorImageHandle,TRUE);
}

