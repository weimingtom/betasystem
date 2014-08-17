#ifndef IncludeGuard_Item_hpp_
#define IncludeGuard_Item_hpp_

#include "System/Vector2.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "Project/Unit/Global.hpp"

//! 
enum ItemID
{
	ItemID_None,
	ItemID_Meet,
	ItemID_Wood,
};


class Item
{
public:
	Item() : mItemID( ItemID_None )
	{
	}
	~Item()
	{
	}
public:
	void Init( ItemID item_id, Vector2 pos, Vector2 speed ){
		mItemID = item_id;
		mPos = pos;
		mSpeed = speed;
	}
	void Update(){
		mPos += mSpeed;
		mSpeed *= 0.9f;
	}
	void Draw(){
		Vector2 const image_size(32,32);
	    DrawGraphInCamera( 
	    	Vector2(
	    		( mPos.x - image_size.x / 2 ),
				( mPos.y - image_size.y )
			),
			image_size,
			mItemID,
			PrincessImageLoader::ImageType_Item,
			TRUE );
	}
	ItemID GetItemID() const { return mItemID; }
	void Reset(){ mItemID = ItemID_None; }
	bool IsValid() const {  return ( mItemID != ItemID_None ); }
	Vector2 GetPos() const { return mPos; }
private:
	Vector2 mPos;
	Vector2 mSpeed;
	ItemID mItemID;
};

//! フィールドに落ちてるアイテム.
class FieldItemManager
{
public:
	void RandamDrop()
	{
		for( int i = 0 ; i < kItemNum ; i++ ){
			DropItem( ItemID_Meet, Vector2( GetRand(1200),GetRand(1200) ) );
		}
	}
	void DropItem( ItemID item_id, Vector2 pos, Vector2 speed = Vector2(0.0f,0.0f) ){
		for( int i = 0 ; i < kItemNum ; i++ ){
			if( mItemList[i].GetItemID() == ItemID_None ){
				mItemList[i].Init( item_id, pos, speed );
				return;
			}
		}
	}
	void Update(){
		for( int i = 0 ; i < kItemNum ; i++ ){
			mItemList[i].Update();
		}
	}
	void Draw(){
		for( int i = 0 ; i < kItemNum ; i++ ){
			mItemList[i].Draw();
		}
	}
	// アイテム情報の取得.
	Item& Reference( int index ){
		return mItemList[index];
	}
	// この座標に落ちてる？
	int CheckDropped( Vector2 pos ){
		for( int i = 0 ; i < kItemNum ; i++ ){
			if( mItemList[i].IsValid() ){
				Vector2 const tmp = mItemList[i].GetPos() - pos;
				if( tmp.Length() < 30 ){
					return i;
				}
			}
		}
		return -1;
	}
private:
	static int const kItemNum = 32;
private:
	Item mItemList[kItemNum];
};

FieldItemManager& gFieldItemManager();


//! プレイヤーのアイテム.
class PlayerItemList
{
public:
	Item& Reference(int index){
		return mItemList[index];
	}
private:
	static int const kItemNum = 10;
private:
	Item mItemList[kItemNum];
};

PlayerItemList& gPlayerItemList();


#endif // IncludeGuard_Item_hpp_

