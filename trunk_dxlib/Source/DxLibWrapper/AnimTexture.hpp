#ifndef include_79f11eca_7022_4d7f_96a5_8d7f678dbe46
#define include_79f11eca_7022_4d7f_96a5_8d7f678dbe46

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
	AnimTexture( int image_handle, AnimData const& anim_data );
	~AnimTexture();
	
public:
	/**
		更新処理.
	*/
	void Update();
	/**
		描画処理.
	*/
	void Draw( Vector2 camera_pos ) const;
	/**
		表示位置の設定.
	*/
	void Set( Vector2 pos );
	/**
		アニメーションの切り替え.
	*/
	void Set( AnimData const& anim_data );

private:
	int m_frame;		//!< フレームカウント.
	int m_anim_index;	//!< 今表示するインデックス.
	int remain_loop;	//!< 残りループ回数.
	Vector2 m_pos;		//!< 表示位置.
};

#endif //include_79f11eca_7022_4d7f_96a5_8d7f678dbe46

