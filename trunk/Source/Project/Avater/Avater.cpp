#include "Avater.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

Avater::Avater( ItemInfo equip_list[EquipPos_Num] )
{
}

Avater::~Avater()
{
}

void Avater::Draw(int x,int y) const
{
	int const width = 200;
	int const height = 200;
	
	//“ª
	DrawRectGraph(
		x, y,
		0, 600,
		width,height,
		ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Avater),
		TRUE, FALSE);
	//”¯
	DrawRectGraph(
		x,y,
		0, 800,
		width,height,
		ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Avater),
		TRUE, FALSE);
	//Šç
	DrawRectGraph(
		x,y,
		0, 0,
		width,height,
		ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Avater),
		TRUE, FALSE);

	//•ž
	DrawRectGraph(
		x,y,
		0, 400,
		width,height,
		ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Avater),
		TRUE, FALSE);

	//ƒIƒvƒVƒ‡ƒ“
	DrawRectGraph(
		x,y,
		0, 200,
		width,height,
		ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Avater),
		TRUE, FALSE);
}


