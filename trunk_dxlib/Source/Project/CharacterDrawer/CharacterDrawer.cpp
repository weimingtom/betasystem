#include "CharacterDrawer.hpp"
#include "DxLibWrapper/Color.hpp"

CharacterDrawer::CharacterDrawer()
{
}

CharacterDrawer::~CharacterDrawer()
{
}

void CharacterDrawer::Update()
{
}

void CharacterDrawer::Draw() const
{
    DrawFormatString( 0 , 300 , ColorOf(0,255,0) , "キャラクターどろわーです。どうも。" );
}

