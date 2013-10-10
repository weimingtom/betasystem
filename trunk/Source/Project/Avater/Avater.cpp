#include "Avater.hpp"
#include <assert.h>
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "DxLibWrapper/ReturnVariable.hpp"

Avater::Avater( ItemInfo equip_list[EquipPos_Num] )
 : mHairImageHandle(0)
{
    for( int i = 0 ; i < EquipPos_Num ; i++ ){
        mEquipList[i] = equip_list[i];
    }

    //髪の毛ハンドルの生成.
    {
        //パレット書き換え.
        int const soft_image_handle = ProjectImageLoader::SoftImageHandleOf( ProjectImageLoader::ImageType_Avater );
        int const target_palette = 2;
        int r,g,b;
        GetColor2( mEquipList[EquipPos_Hair].color , &r,&g,&b);
        SetPaletteSoftImage( soft_image_handle, target_palette, r, g, b, 0 ) ;
        //イメージハンドル作成.
        mHairImageHandle = CreateGraphFromSoftImage(soft_image_handle);
    }
}

Avater::~Avater()
{
    //ハンドルの削除.
	if( DeleteGraph( mHairImageHandle ) == FunctionFailure ){
		assert( false );
	}
}

void Avater::Draw(int x,int y) const
{
	int const width = 200;
	int const height = 200;
	
	//頭
	DrawRectGraph(
		x, y,
		0, 600,
		width,height,
		ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Avater),
		TRUE, FALSE);
	//髪
	DrawRectGraph(
		x,y,
		0, 800 + mEquipList[EquipPos_Hair].id * height,
		width,height,
		mHairImageHandle,
		TRUE, FALSE);
	//顔
	DrawRectGraph(
		x,y,
		0, 0,
		width,height,
		ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Avater),
		TRUE, FALSE);
	//服
	DrawRectGraph(
		x,y,
		mEquipList[EquipPos_Body].id * width, 400,
		width,height,
		ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Avater),
		TRUE, FALSE);
}


