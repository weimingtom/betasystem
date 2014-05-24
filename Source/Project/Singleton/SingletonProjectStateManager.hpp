#ifndef include_4043f656_29d2_4fa5_b7b8_641d2d447994
#define include_4043f656_29d2_4fa5_b7b8_641d2d447994

#include <string>
#include "../../System/StateManagerBase.hpp"

namespace Princess{

	/**
    プロジェクトの一番上に位置するStateManager.
*/
class ProjectStateManager : public StateManagerBase
{
public:
    //! ステート.
    enum State{
        State_DebugTop,     //!< デバッグトップ
        State_LuaTest,      //!< 
        State_Num,
    };
public:
    //! デストラクタ.
    ~ProjectStateManager();
public:
    //! ステートマネージャのポインタ取得.
    static ProjectStateManager* GetInstance();
    //! インスタンスの削除.
    static void DeleteInstance();
    //! ステートインスタンスの生成.
    //! @param state 生成したいステートの種類.
    static StateBase* new_State(State state);
    //! 名前の取得.
    static std::string NameOf(State state);
private:
    //! コンストラクタ.
    ProjectStateManager();
};

}

#endif

