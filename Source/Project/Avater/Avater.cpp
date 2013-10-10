#include "Avater.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

Avater::Avater( ItemInfo equip_list[EquipPos_Num] )
{
    for( int i = 0 ; i < EquipPos_Num ; i++ ){
        mEquipList[i] = equip_list[i];
    }
}

Avater::~Avater()
{
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
		ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Avater),
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

	//オプション
	DrawRectGraph(
		x,y,
		0, 200,
		width,height,
		ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Avater),
		TRUE, FALSE);
}


