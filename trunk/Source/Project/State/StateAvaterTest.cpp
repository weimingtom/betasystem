#include "StateAvaterTest.hpp"

#include <assert.h>
#include "Project/Draw.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "System/StateManagerBase.hpp"
#include "System/ArraySize.hpp"
#include "System/Range.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "Project/SaveData.hpp"


char const* NameOf(AvaterType type)
{
	static char const* name[AvaterType_Num] = 
	{
		"オプション",
		"服",
		"髪型",
		"髪色",
		"顔の種類",
	};
	return name[type];
}

int MaxOf(AvaterType type)
{
	switch(type)
	{
	case AvaterType_Cloth:
		return Cloth_Num;
	case AvaterType_Face:
		return Face_Num;
	case AvaterType_Hair:
		return Hair_Num;
	case AvaterType_HairColor:
		return HairColor_Num;
	case AvaterType_Option:
		return Option_Num;
	default:
		assert(false);
		return 0;
	}
}

char const* NameOf( AvaterType type, int index_x)
{
	switch(type)
	{
	case AvaterType_Cloth:
		return NameOf( static_cast<TypeCloth>(index_x) );
	case AvaterType_Face:
		return NameOf( static_cast<TypeFace>(index_x) );
	case AvaterType_Hair:
		return NameOf( static_cast<TypeHair>(index_x) );
	case AvaterType_HairColor:
		return NameOf( static_cast<TypeHairColor>(index_x) );
	case AvaterType_Option:
		return NameOf( static_cast<TypeOption>(index_x) );
	default:
		assert(false);
		return "";
	}
}

//アバターの描画
void Draw(int x,int y,AvaterParam const& param)
{
	int const width = 200;
	int const height = 200;
	
	//頭
	DrawPartOfTexture( ImageType_Avater, Vector2(x,y), Vector2(0,3*200), Vector2(width,height) );
	//髪
	DrawPartOfTexture( ImageType_Avater, Vector2(x,y), Vector2( width * param.hair_color , 800 + param.hair * 200), Vector2(width,height) );
	//顔
	DrawPartOfTexture( ImageType_Avater, Vector2(x,y), Vector2( width * param.face , 0*200), Vector2(width,height) );
	//服
	DrawPartOfTexture( ImageType_Avater, Vector2(x,y), Vector2( width * param.cloth , 2*200), Vector2(width,height) );
	//オプション
	DrawPartOfTexture( ImageType_Avater, Vector2(x,y), Vector2( width * param.option ,200), Vector2(width,height) );
}

StateAvaterTest::StateAvaterTest( StateManagerBase* manager )
 : m_manager( manager )
{
}

void StateAvaterTest::Update()
{
    if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_Up ) ) )
	{
		m_select_y--;
	}
	else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_Down ) ) )
	{
		m_select_y++;
	}
	else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_Left ) ) )
	{
		m_select_x[m_select_y]--;
	}
	else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_Right ) ) )
	{
		m_select_x[m_select_y]++;
	}
	
	m_select_y = Clamp(0,m_select_y,AvaterType_Num-1);
	for( int i = 0 ; i < AvaterType_Num ; i ++ ){
		m_select_x[i] = Clamp( 0 , m_select_x[i] , MaxOf( static_cast<AvaterType>(i) ) - 1 );
	}

	m_avater.cloth = static_cast<TypeCloth>( m_select_x[AvaterType_Cloth] );
	m_avater.face = static_cast<TypeFace>( m_select_x[AvaterType_Face] );
	m_avater.hair = static_cast<TypeHair>( m_select_x[AvaterType_Hair] );
	m_avater.hair_color = static_cast<TypeHairColor>( m_select_x[AvaterType_HairColor] );
	m_avater.option = static_cast<TypeOption>( m_select_x[AvaterType_Option] );

}

void StateAvaterTest::Draw() const
{
	DrawBox(0,0,640,480,ColorOf(255,255,255),TRUE);
    DrawFormatString( 0 , 0 , ColorOf(0,255,0) , "アバター描画テスト");
	
    DrawFormatString( 0 , 20 + m_select_y*14 , ColorOf(0,255,0) , "→");
	for(int i = 0 ; i < AvaterType_Num ; i++ ){
	    DrawFormatString( 20 , 20 + i*14 , ColorOf(0,255,0) , "%s:%s",
	    	NameOf( static_cast<AvaterType>(i) ), NameOf( static_cast<AvaterType>(i), m_select_x[i] ) );
	}

	//アバターの描画.
	::Draw(100,100,m_avater);

}

