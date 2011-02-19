#ifndef include_79f11eca_7022_4d7f_96a5_8d7f678dbe46
#define include_79f11eca_7022_4d7f_96a5_8d7f678dbe46

#include "System/AnimFormat.hpp"
#include "System/Vector2.hpp"

/**
	アニメーションするテクスチャを実現するクラス.
*/
class AnimTexture
{
public:
	/**
		@param image_handle 表示する画像のハンドル.
		@param anim_data アニメーションデータ.
	*/
	AnimTexture( int image_handle, AnimFormat const& anim_data );
	~AnimTexture(){}
	
public:
	/**
		更新処理.
	*/
	void Update();
	/**
		描画処理.
	*/
	void Draw( Vector2 const& camera_pos ) const;
	/**
		表示位置の設定.
	*/
	void Set( Vector2 const& pos ){ m_pos = pos; }
	/**
		アニメーションの切り替え.
	*/
	void Set( AnimFormat const& anim_data );

private:
    int m_image_handle;
	int m_frame;		//!< フレームカウント.
	int m_current_index;	//!< 今表示するインデックス.
	int m_remain_loop;	//!< 残りループ回数.
	Vector2 m_pos;		//!< 表示位置.
    AnimFormat m_anim_data; //!< 元のアニメデータ.
};

#endif //include_79f11eca_7022_4d7f_96a5_8d7f678dbe46

