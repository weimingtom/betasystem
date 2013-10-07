#include "StateGameMain.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include "Project/PlayerStatus.h"
#include "Project/KoyakuType.h"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"

StateGameMain::StateGameMain()
 : mLogPrinter( new_LogPrinter(100,300) )
{
	srand( static_cast<unsigned int>( time(NULL) ) );
}

void StateGameMain::Update()
{
    if( KeyInput()->IsTrig( InputKey::Type_Enter ) )
	{
		//抽選処理.
		int const kOnePlayCoin = 3;
		mPlayerStatus.coin -= kOnePlayCoin;
		DrawingResult const drawing_result = GetDrawingResult( mPlayerStatus.drawing_status );
		mPlayerStatus.coin += CoinOf(drawing_result.koyaku_type);
		std::stringstream ss;
		ss << "抽選結果:" << NameOf(drawing_result.koyaku_type) << ":" << drawing_result.is_art 
		    << "プレイヤー情報:" << mPlayerStatus.coin << ":" << mPlayerStatus.drawing_status ;
		mLogPrinter->Print(ss.str());
		
		mKoyakuList.insert( mKoyakuList.begin() , drawing_result.koyaku_type );
		if( mKoyakuList.size() > kKoyakuListMax ){
		    mKoyakuList.pop_back();
		}
	}
}

void StateGameMain::Draw() const
{
    int const kIconWidth = 32;
    int const kIconHeight = 32;
    int const kDrawX = 400;
    int const kDrawY = 300;
    
	for( std::string::size_type i = 0 ; i < kKoyakuListMax && i < mKoyakuList.size() ; i++ ){
        DrawRectGraph(
            kDrawX, kDrawY - i * kIconHeight,
            0, mKoyakuList.at(i)*kIconHeight,
            kIconWidth, kIconHeight,
            ProjectImageLoader::ImageHandleOf(ProjectImageLoader::ImageType_Koyaku),
            TRUE , FALSE );
        DrawFormatString( 0 , 0 , GetColor(0,255,0) , "ゲームメイン");
        mLogPrinter->Draw();
    }
}
