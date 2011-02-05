#ifndef include_b122a87f_b25d_4192_b94d_5e7589771cd3
#define include_b122a87f_b25d_4192_b94d_5e7589771cd3

#include "DxLibWrapper/InputMouse.hpp"

/**
	プロジェクト唯一のマウスインターフェース.
*/
namespace SingletonInputMouse
{
	/**
		初期化.
	*/
	void Init();
	/**
		更新.
	*/
	void Update();
	/**
		インスタンスの取得.
	*/
	InputMouse* Get();
};

#endif // include_b122a87f_b25d_4192_b94d_5e7589771cd3
