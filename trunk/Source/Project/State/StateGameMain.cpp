#include "StateGameMain.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include "Project/DrawingKoyaku.h"
#include "Project/PlayerStatus.h"
#include "Project/KoyakuType.h"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Singleton/SingletonProjectStateManager.hpp"

StateGameMain::StateGameMain()
 : mLogPrinter( new_LogPrinter(100,100) )
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
		ss << "抽選結果:" << NameOf(drawing_result.koyaku_type) << ":" << drawing_result.is_art << "\n" 
		    << "プレイヤー情報:" << mPlayerStatus.coin << ":" << mPlayerStatus.drawing_status << "\n";
		mLogPrinter->Print(ss.str());
	}
}

void StateGameMain::Draw() const
{
    mLogPrinter->Draw();
}
