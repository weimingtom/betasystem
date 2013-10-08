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
    //�p���b�g��������.
    SetPaletteSoftImage( mSoftImageHandle, 0, 255, 0, 0, 0 ) ;
    //�C���[�W�n���h���쐬.
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
    DrawFormatString( 0 , 0 , GetColor(0,255,0) , "�p���b�g�e�X�g");
    DrawGraph(0,0,mChangedColorImageHandle,TRUE);
}

